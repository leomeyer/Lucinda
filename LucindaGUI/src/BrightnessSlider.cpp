#include "BrightnessSlider.h"

namespace APP_NAMESPACE {

BrightnessSlider::BrightnessSlider(wxWindow* parent, ChannelPanel* channel, const wxString& name)
    : SliderPanel(parent, channel, SLIDER_BRIGHTNESS, name, 0, 255)
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
