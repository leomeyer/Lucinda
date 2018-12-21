#include "RegularChannelPanel.h"

namespace APP_NAMESPACE {

RegularChannelPanel::RegularChannelPanel(wxWindow* parent, Processor* processor, uint8_t channel)
    : ChannelPanel(parent, processor, "Channel", channel)
{
    addSlider("Frequency", SLIDER_PERIOD);
    addSlider("Phase shift", SLIDER_PHASESHIFT);
    addSlider("Brightness", SLIDER_BRIGHTNESS);
    addSlider("Offset", SLIDER_OFFSET);
    addSlider("Duty Cycle", SLIDER_DUTYCYCLE);
}

RegularChannelPanel::~RegularChannelPanel()
{
    //dtor
}

}; // namespace
