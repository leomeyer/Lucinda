#include "GlobalFrequencySlider.h"

namespace APP_NAMESPACE {

GlobalFrequencySlider::GlobalFrequencySlider(ChannelPanel* channel, const wxString& name)
    : FrequencySlider(channel, SLIDER_GLOBAL_FREQUENCY, name, 0, GLOBAL_FREQUENCY_MAX)
{
    //ctor
}

GlobalFrequencySlider::~GlobalFrequencySlider()
{
    //dtor
}

}; // namespace
