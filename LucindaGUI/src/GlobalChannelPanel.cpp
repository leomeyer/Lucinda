#include "GlobalChannelPanel.h"

#include "ChannelPanel.h"

#include "Context.h"

namespace APP_NAMESPACE {


GlobalChannelPanel::GlobalChannelPanel(wxWindow* parent, Context* context)
    : ChannelPanel(parent, context, "", -1)
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
