#include "PercentSlider.h"

namespace APP_NAMESPACE {

PercentSlider::PercentSlider(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int value, const wxColour* colour)
    : SliderPanel(parent, channel, type, name, 0, 255, value, colour)
{
    setLabels();
    slider->SetValue(value);
    updateControls();
}

PercentSlider::~PercentSlider()
{
    //dtor
}

void PercentSlider::setLabels()
{
//    SliderPanel::setLabels();
    stLabel->SetLabel("%");
    stMinValue->SetLabel("0 %");
    stMaxValue->SetLabel("100 %");
}

wxString PercentSlider::valueToString(const int value)
{
    wxString result = wxString::Format(wxT("%.1f"), value / 255.0f * 100.0f);
/*    while (result.EndsWith("0") || result.EndsWith("."))
        result = result.RemoveLast(1);
*/
    return result;
}

bool PercentSlider::stringToValue(const wxString& str, int& value)
{
    // parse entered value
    double val;
    if (str.ToDouble(&val)) {
        value = val / 100.0f * 256.0f;
        if (value > 255)
            value = 255;
        if (value < 0)
            value = 0;
        return true;
    }
    return false;
}

}; // namespace
