#include "SliderPanel.h"

#include "ChannelPanel.h"
#include "Context.h"
#include "UndoManager.h"

namespace APP_NAMESPACE {

SliderPanel::SliderPanel(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int min, int max, int value,
                    const wxColour* colour)
    : SliderPanelBase(parent)
{
    this->channel = channel;
    this->type = type;
    this->min = min;
    this->max = max;
    slider->SetMin(min);
    slider->SetMax(max);
    setSliderValue(value);
    preTrackValue = -1;

    stSliderName->SetLabel(name);
    setLabels();
    if (colour != nullptr) {
        stSliderName->SetBackgroundColour(*colour);
        // slider->SetForegroundColour(*colour);
    }

}

SliderPanel::~SliderPanel()
{
}

SliderType SliderPanel::getType()
{
    return type;
}

uint16_t SliderPanel::getValue()
{
    return getDeviceValue(slider->GetValue());
}

void SliderPanel::setSliderValue(int value)
{
    slider->SetValue(value);
    // store current value
    currentValue = slider->GetValue();

    updateControls();
}

int SliderPanel::getDeviceValue(int sliderValue)
{
    return sliderValue;
}

wxString SliderPanel::valueToString(const int value)
{
    wxString result;
    result << value;
    return result;
}

bool SliderPanel::stringToValue(const wxString& str, int& value)
{
    // parse entered value
    long val;
    if (str.ToLong(&val)) {
        value = (int)val;
        return true;
    }
    return false;
}

void SliderPanel::setLabels()
{
    stMinValue->SetLabel(valueToString(min));
    stMaxValue->SetLabel(valueToString(max));
    updateControls();
}

void SliderPanel::OnFocusValue(wxFocusEvent& event)
{
    // select all text
    txtValue->SelectAll();
    event.Skip();
};

void SliderPanel::OnValCharHook(wxKeyEvent& event)
{
    int previousValue = currentValue;

    // shift, ctrl and alt accelerate change to different degrees
    int increment = 1;
    if (event.ShiftDown())
        increment = slider->GetPageSize();
    if (event.AltDown())
        increment *= 2;
    if (event.ControlDown())
        increment *= 4;

    if (event.GetKeyCode() == wxKeyCode::WXK_UP) {
        setSliderValue(slider->GetValue() + increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_DOWN) {
        setSliderValue(slider->GetValue() - increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_PAGEUP) {
        setSliderValue(slider->GetValue() + slider->GetPageSize() * increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_PAGEDOWN) {
        setSliderValue(slider->GetValue() - slider->GetPageSize() * increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_HOME && event.ControlDown()) {
        setSliderValue(slider->GetMax());
    } else if (event.GetKeyCode() == wxKeyCode::WXK_END && event.ControlDown()) {
        setSliderValue(0);
    } else {
        event.Skip();
        return;
    }
    // for unknown reasons the OnSlider isn't fired as documented,
    // so we have to do this manually
    txtValue->SelectAll();

    if (previousValue != slider->GetValue())
        applyUndoableChange(previousValue);
}

void SliderPanel::OnValueEnter(wxCommandEvent& event)
{
    int previousValue = currentValue;

    // parse entered value
    int value;

    if (stringToValue(txtValue->GetValue(), value)) {
        if (value > max)
            value = max;
        if (value < min)
            value = min;
        setSliderValue(value);
    }
    // select all text
    txtValue->SelectAll();

    if (previousValue != slider->GetValue())
        applyUndoableChange(previousValue);
}

void SliderPanel::OnSliderRelease(wxScrollEvent& event)
{
    // protocol all changes as one undo event
    applyUndoableChange(preTrackValue);
    setSliderValue(slider->GetValue());
    preTrackValue = -1;
}

void SliderPanel::OnSliderTrack(wxScrollEvent& event)
{
    preTrackValue = currentValue;  // value at start of tracking
    channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));
    updateControls();
}

void SliderPanel::OnSlider(wxCommandEvent& event)
{
    // tracking?
    if (preTrackValue >= 0)
        return;

    int previousValue = currentValue;
    setSliderValue(slider->GetValue());

    applyUndoableChange(previousValue);
}

void SliderPanel::updateControls()
{
    int value = slider->GetValue();
    wxString txt = valueToString(value);
    txtValue->SetValue(txt);
}

// undo/redo logic

void SliderPanel::applyUndoableChange(int previousValue)
{
    // important! OnSlider will generate multiple events after tracking has been released
    // so generating undo changes with the same value must be avoided
    if (slider->GetValue() != previousValue) {
        // register change, store previous and current slider value
        SliderUndoInfo* data = new SliderUndoInfo();
        data->previous = previousValue;
        data->current = slider->GetValue();
        UndoChange* undoChange = new UndoChange(this, 0, stSliderName->GetLabel(), data);

        channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));

        channel->context->undoManager->addUndoChange(undoChange);
    }
}

void SliderPanel::undo(UndoChange* change)
{
    SliderUndoInfo* data = (SliderUndoInfo*)change->data;
    setSliderValue(data->previous);
    channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));
}

void SliderPanel::redo(UndoChange* change)
{
    SliderUndoInfo* data = (SliderUndoInfo*)change->data;
    setSliderValue(data->current);
    channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));
}


}; // namespace
