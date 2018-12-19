#include "ChannelPanel.h"

#include "SliderPanel.h"
#include "PercentSlider.h"
#include "FrequencySlider.h"

#include "Processor.h"

namespace APP_NAMESPACE {

ChannelPanel::ChannelPanel(wxWindow* parent, Processor* processor, const wxString& name, int number)
    : ChannelPanelBase(parent)
{
    this->processor = processor;
    this->channel = number;
    sliderCount = 0;

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
    // construct slider depending on type
    SliderPanelBase* slider;
    switch (type) {
        case SLIDER_BRIGHTNESS: slider = new PercentSlider(pInternal, this, type, name); break;
        case SLIDER_GLOBAL_SPEED: slider = new SliderPanel(pInternal, this, type, name, 0, GLOBAL_SPEED_MAX); break;
        case SLIDER_PERIOD: slider = new FrequencySlider(pInternal, this, type, name, CHANNEL_PERIOD_MAX); break;
        case SLIDER_PHASESHIFT: slider = new PercentSlider(pInternal, this, type, name); break;
        case SLIDER_OFFSET: slider = new PercentSlider(pInternal, this, type, name); break;
        case SLIDER_DUTYCYCLE: slider = new PercentSlider(pInternal, this, type, name); break;
        default: return;
    }

    sizerInternal->Add(slider, 0, wxALL, 1);

    sliderCount++;
    wxSize cSize = GetClientSize();
    wxSize pSize = slider->GetMinSize();
    SetClientSize(wxSize(cSize.x + pSize.x, cSize.y));
    SetMinSize(wxSize(sliderCount * pSize.x + 20, cSize.y));

    channelSizer->Fit(pInternal);
}

void ChannelPanel::OnSliderChange(SliderType type, int value)
{
    processor->OnValueChange(channel, type, value);
}


}; // namespace
