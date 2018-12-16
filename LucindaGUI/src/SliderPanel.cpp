#include "SliderPanel.h"

#include "ChannelPanel.h"

namespace APP_NAMESPACE {


SliderPanel::SliderPanel(ChannelPanel* channel, SliderType type, const wxString& name, int min, int max)
    : SliderPanelBase(channel)
{
    this->channel = channel;
    this->type = type;

    stSliderName->SetLabel(name);

    slider->SetMin(min);
    stMinValue->SetLabel(std::to_string(min));
    slider->SetMax(max);
    stMaxValue->SetLabel(std::to_string(max));
    slider->SetValue((max - min / 2));

    UpdateControls();
}

SliderPanel::~SliderPanel()
{
    //dtor
}

void SliderPanel::OnFocusValue(wxFocusEvent& event)
{
    // select all text
    txtValue->SelectAll();
    event.Skip();
}

void SliderPanel::OnValueEnter(wxCommandEvent& event)
{
    // parse entered value
    long value;
    if (txtValue->GetValue().ToLong(&value)) {
        if (value > slider->GetMax())
            value = slider->GetMax();
        if (value < slider->GetMin())
            value = slider->GetMin();
        slider->SetValue(value);
    }
    UpdateControls();
    // select all text
    txtValue->SelectAll();

    channel->OnSliderChange(type, slider->GetValue());
}

void SliderPanel::OnSlider(wxCommandEvent& event)
{
    UpdateControls();

    channel->OnSliderChange(type, slider->GetValue());
}

void SliderPanel::UpdateControls()
{
    wxString val;
    val << slider->GetValue();
    txtValue->SetValue(val);
}


}; // namespace
