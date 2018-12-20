#include "GlobalChannelPanel.h"

#include "ChannelPanel.h"

#include "Processor.h"

namespace APP_NAMESPACE {


GlobalChannelPanel::GlobalChannelPanel(wxWindow* parent, Processor* processor)
    : ChannelPanel(parent, processor, "", -1)
{
    stChannelName->SetLabel("Global");

    pControls->Hide();
    addSlider("Brightness", SLIDER_BRIGHTNESS);
//    addSlider("Speed", SLIDER_GLOBAL_SPEED);
}

GlobalChannelPanel::~GlobalChannelPanel()
{
    //dtor
}

}; // namespace
