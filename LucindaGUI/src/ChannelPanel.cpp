#include "ChannelPanel.h"

#include "SliderPanel.h"

#include "Processor.h"

namespace APP_NAMESPACE {

ChannelPanel::ChannelPanel(wxWindow* parent, Processor* processor, const wxString& name, int number)
    : ChannelPanelBase(parent)
{
    this->processor = processor;
    this->channel = number;

    wxString cName = name;
    cName << " (Channel " << number << ")";
    stChannelName->SetLabel(cName);
}

ChannelPanel::~ChannelPanel()
{
    //dtor
}

void ChannelPanel::addSlider(const wxString& name, SliderType type)
{
    int min = 0;
    int max = 255;

    SliderPanel* slider = new SliderPanel(this, type, name, min, max);
    bSizerInternal->Add(slider, 1, wxALL|wxEXPAND, 1);
}

void ChannelPanel::OnSliderChange(SliderType type, int value)
{
    processor->OnValueChange(channel, type, value);
}


}; // namespace
