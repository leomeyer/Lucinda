#ifndef COLORMANAGEMENT_H
#define COLORMANAGEMENT_H

#include "GlobalDefines.h"

#include <wx/wx.h>

namespace APP_NAMESPACE {

class ColorManagement
{
    public:
        ColorManagement();
        virtual ~ColorManagement();

        const wxColour* getBrightnessColor();
        const wxColour* getFrequencyColor();
        const wxColour* getPhaseshiftColor();
        const wxColour* getOffsetColor();
        const wxColour* getDutycycleColor();

    protected:
        wxColour lightBlue;

    private:
};

}; // namespace

#endif // COLORMANAGEMENT_H
