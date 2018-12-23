#include "SliderPanel.h"

#include "ChannelPanel.h"

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
    slider->SetValue(value);

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
    // shift, ctrl and alt accelerate change to different degrees
    int increment = 1;
    if (event.ShiftDown())
        increment = slider->GetPageSize();
    if (event.AltDown())
        increment *= 2;
    if (event.ControlDown())
        increment *= 4;

    if (event.GetKeyCode() == wxKeyCode::WXK_UP) {
        slider->SetValue(slider->GetValue() + increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_DOWN) {
        slider->SetValue(slider->GetValue() - increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_PAGEUP) {
        slider->SetValue(slider->GetValue() + slider->GetPageSize() * increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_PAGEDOWN) {
        slider->SetValue(slider->GetValue() - slider->GetPageSize() * increment);
    } else if (event.GetKeyCode() == wxKeyCode::WXK_HOME && event.ControlDown()) {
        slider->SetValue(slider->GetMax());
    } else if (event.GetKeyCode() == wxKeyCode::WXK_END && event.ControlDown()) {
        slider->SetValue(0);
    } else {
        event.Skip();
        return;
    }
    // for unknown reasons the OnSlider isn't fired as documented,
    // so we have to do this manually
    updateControls();
    txtValue->SelectAll();
    channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));
}


void SliderPanel::OnValueEnter(wxCommandEvent& event)
{
    // parse entered value
    int value;

    if (stringToValue(txtValue->GetValue(), value)) {
        if (value > max)
            value = max;
        if (value < min)
            value = min;
        slider->SetValue(value);
    }
    updateControls();
    // select all text
    txtValue->SelectAll();

    channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));
}

void SliderPanel::OnSlider(wxCommandEvent& event)
{
    updateControls();

    channel->OnSliderChange(type, getDeviceValue(slider->GetValue()));
}

void SliderPanel::updateControls()
{
    int value = slider->GetValue();
    wxString txt = valueToString(value);
    txtValue->SetValue(txt);
}

}; // namespace
