#include "FrequencySlider.h"

namespace APP_NAMESPACE {

FrequencySlider::FrequencySlider(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int min, int max)
    : SliderPanel(parent, channel, type, name, min, max)
{
    setLabels();
}

FrequencySlider::~FrequencySlider()
{
    //dtor
}

int FrequencySlider::getDeviceValue(int sliderValue)
{
    if (sliderValue == 0)
        return 0;
    return max - sliderValue;
}

wxString FrequencySlider::valueToString(const int value)
{
    if (value == 0)
        return "0 (Off)";

    return wxString::Format(wxT("%.2f"), 1.0f * value / (max / 2));
}

bool FrequencySlider::stringToValue(const wxString& str, int& value)
{
    // parse entered value
    double val;
    if (str.ToDouble(&val)) {
        value = (float)val;
        if (value == 0)
            value = 0;
        else
            value = 1;

        return true;
    }
    return false;
}

void FrequencySlider::setLabels()
{
    stLabel->SetLabel("Hz");
    SliderPanel::setLabels();
}

}; // namespace
