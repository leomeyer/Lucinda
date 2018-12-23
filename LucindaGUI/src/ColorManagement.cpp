#include "ColorManagement.h"

namespace APP_NAMESPACE {

ColorManagement::ColorManagement()
{
    lightBlue = wxColour(200, 200, 255);
}

ColorManagement::~ColorManagement()
{
    //dtor
}

const wxColour* ColorManagement::getBrightnessColor()
{
    return wxYELLOW;
}

const wxColour* ColorManagement::getFrequencyColor()
{
    return &lightBlue;
}

const wxColour* ColorManagement::getPhaseshiftColor()
{
    return wxGREEN;
}

const wxColour* ColorManagement::getOffsetColor()
{
    return wxLIGHT_GREY;
}

const wxColour* ColorManagement::getDutycycleColor()
{
    return wxRED;
}

}; // namespace
