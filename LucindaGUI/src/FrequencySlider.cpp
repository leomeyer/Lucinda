#include "FrequencySlider.h"

namespace APP_NAMESPACE {

#define FREQ_MAX    512

FrequencySlider::FrequencySlider(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int deviceMax, int value)
    : SliderPanel(parent, channel, type, name, 0, FREQ_MAX - 1, value)
{
    this->deviceMax = deviceMax;
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
    return deviceMax - 1 - (deviceMax - 1) * sqrt(log(sliderValue * deviceMax / FREQ_MAX) / log(deviceMax));
}

wxString FrequencySlider::valueToString(const int value)
{
    if (value == 0)
        return "0 (Off)";

    wxString result = wxString::Format(wxT("%.2f"), 1024.0f / getDeviceValue(value));
    while (result.EndsWith("0") || result.EndsWith("."))
        result = result.RemoveLast(1);
    return result;
}

bool FrequencySlider::stringToValue(const wxString& str, int& value)
{
    // parse entered value
    double val;
    if (str.ToDouble(&val)) {
        if (val == 0)
            value = 0;
        else {
            float dev = 1024.0f / val;
            value = pow(2.71828, 1.0f * pow((deviceMax - 1 - dev), 2) / pow((deviceMax - 1), 2) * log(deviceMax - 1)) * FREQ_MAX / deviceMax;
            if (value == 0)
                value = 1;
        }
        return true;
    }
    return false;
}

void FrequencySlider::setLabels()
{
    stLabel->SetLabel("Hz");
    SliderPanel::setLabels();
    stMaxValue->SetLabel(stMaxValue->GetLabel() + " Hz");
}

}; // namespace
