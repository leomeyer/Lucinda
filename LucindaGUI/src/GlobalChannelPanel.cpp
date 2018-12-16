#include "GlobalChannelPanel.h"

#include "ChannelPanel.h"

#include "Processor.h"

namespace APP_NAMESPACE {


GlobalChannelPanel::GlobalChannelPanel(wxWindow* parent, Processor* processor)
    : ChannelPanel(parent, processor, "", -1)
{
    stChannelName->SetLabel("Global");

    addSlider("Brightness", SLIDER_BRIGHTNESS);
//    bContentSizer->Add(panel, 0, wxALL|wxEXPAND, 5);
}

GlobalChannelPanel::~GlobalChannelPanel()
{
    //dtor
}

}; // namespace
