#include "BrightnessSlider.h"

namespace APP_NAMESPACE {

BrightnessSlider::BrightnessSlider(wxWindow* parent, ChannelPanel* channel, const wxString& name, int value)
    : SliderPanel(parent, channel, SLIDER_BRIGHTNESS, name, 0, 255, value)
{
}

BrightnessSlider::~BrightnessSlider()
{
    //dtor
}

void BrightnessSlider::setLabels()
{
    SliderPanel::setLabels();
    stLabel->SetLabel("Level");
}

}; // namespace
