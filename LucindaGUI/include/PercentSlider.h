#ifndef PERCENTSLIDER_H
#define PERCENTSLIDER_H

#include "GlobalDefines.h"

#include <SliderPanel.h>

namespace APP_NAMESPACE {

class PercentSlider : public SliderPanel
{
    public:
        PercentSlider(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name);
        virtual ~PercentSlider();

    protected:
        virtual void setLabels();

        virtual wxString valueToString(const int value) override;

        virtual bool stringToValue(const wxString& str, int& value) override;

    private:
};

}; // namespace

#endif // PERCENTSLIDER_H
