#include "Processor.h"

#include "Context.h"

#include "ChannelPanel.h"
#include "Controller.h"

namespace APP_NAMESPACE {

Processor::Processor(Controller* controller)
{
    this->controller = controller;
}

Processor::~Processor()
{
    //dtor
}

void Processor::OnValueChange(int channel, SliderType type, int value)
{
    wxString msg = "Channel ";
    msg << channel;
    msg << " slider ";
    switch (type) {
    case SLIDER_GLOBAL_SPEED: msg << " Global speed"; break;
    case SLIDER_BRIGHTNESS: msg << " Brightness"; break;
    case SLIDER_PERIOD: msg << " Period"; break;
    case SLIDER_PHASESHIFT: msg << " Phase shift"; break;
    case SLIDER_OFFSET: msg << " Offset"; break;
    case SLIDER_DUTYCYCLE: msg << " Duty cycle"; break;
    case SLIDER_UNKNOWN: msg << " Unknown"; break;
    }
    msg << " changed to: ";
    msg << value;
    controller->getContext()->logger->logDebug(msg);

    if (channel == -1) {
        controller->sendGlobalValue(type, value);
    } else {
        controller->sendChannelValue(channel, type, value);
    }
}

void Processor::OnSendChannelSettings(ChannelPanel* panel, bool apply)
{
    controller->sendChannelSettings(panel, apply);
}


}; // namespace
