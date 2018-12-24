#include "RegularChannelPanel.h"

#include "Context.h"

namespace APP_NAMESPACE {

RegularChannelPanel::RegularChannelPanel(wxWindow* parent, Controller* controller, uint8_t channel)
    : ChannelPanel(parent, controller, "Channel", channel)
{
    pGlobalControls->Hide();

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
