#include "SliderPanel.h"

#include "ChannelPanel.h"

namespace APP_NAMESPACE {

SliderPanel::SliderPanel(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int min, int max)
    : SliderPanelBase(parent)
{
    this->channel = channel;
    this->type = type;
    this->min = min;
    this->max = max;
    slider->SetMin(min);
    slider->SetMax(max);

    stSliderName->SetLabel(name);
    slider->SetValue((max - min) / 2);
    setLabels();
}

SliderPanel::~SliderPanel()
{

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

    channel->OnSliderChange(type, slider->GetValue());
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
