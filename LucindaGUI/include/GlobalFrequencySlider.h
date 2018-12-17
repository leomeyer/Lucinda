#ifndef GLOBALFREQUENCYSLIDER_H
#define GLOBALFREQUENCYSLIDER_H

#include "GlobalDefines.h"

#include <FrequencySlider.h>

namespace APP_NAMESPACE {


class GlobalFrequencySlider : public FrequencySlider
{
    public:
        GlobalFrequencySlider(ChannelPanel* channel, const wxString& name);
        virtual ~GlobalFrequencySlider();

    protected:

    private:
};

}; // namespace

#endif // GLOBALFREQUENCYSLIDER_H
