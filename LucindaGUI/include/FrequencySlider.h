#ifndef FREQUENCYSLIDER_H
#define FREQUENCYSLIDER_H

#include "GlobalDefines.h"

#include <SliderPanel.h>

namespace APP_NAMESPACE {

class FrequencySlider : public SliderPanel
{
    public:
        FrequencySlider(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int deviceMax, int value,
                        const wxColour* color = nullptr);
        virtual ~FrequencySlider();

    protected:

        int deviceMax;

        virtual int getDeviceValue(int sliderValue) override;

        virtual wxString valueToString(const int value) override;

        virtual bool stringToValue(const wxString& str, int& value) override;

        virtual void setLabels() override;

    private:
};

}; // namespace

#endif // FREQUENCYSLIDER_H
