#ifndef BRIGHTNESSSLIDER_H
#define BRIGHTNESSSLIDER_H

#include "GlobalDefines.h"

#include <SliderPanel.h>

namespace APP_NAMESPACE {

class BrightnessSlider : public SliderPanel
{
    public:
        BrightnessSlider(wxWindow* parent, ChannelPanel* channel, const wxString& name, int value);
        virtual ~BrightnessSlider();

    protected:
        virtual void setLabels();

    private:
};

}; // namespace

#endif // BRIGHTNESSSLIDER_H
