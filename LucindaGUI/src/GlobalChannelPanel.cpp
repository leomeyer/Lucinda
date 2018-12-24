#include "GlobalChannelPanel.h"

#include "ChannelPanel.h"
#include "SliderPanel.h"

#include "Context.h"

namespace APP_NAMESPACE {


GlobalChannelPanel::GlobalChannelPanel(wxWindow* parent, Controller* controller)
    : ChannelPanel(parent, controller, "", -1)
{
    stChannelName->SetLabel("Global");

    pControls->Hide();
    pGlobalControls->Show();

    addSlider("Brightness", SLIDER_BRIGHTNESS)->setSliderValue(255);
//    addSlider("Speed", SLIDER_GLOBAL_SPEED);
}

GlobalChannelPanel::~GlobalChannelPanel()
{
    //dtor
}

}; // namespace
