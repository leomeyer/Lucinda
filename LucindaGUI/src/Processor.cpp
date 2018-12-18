#include "Processor.h"

#include "Context.h"
#include "ApplicationController.h"

namespace APP_NAMESPACE {

Processor::Processor(ApplicationController* controller)
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
    case SLIDER_BRIGHTNESS: msg << " Brightness"; break;
    case SLIDER_PERIOD: msg << " Period"; break;
    }
    msg << " changed to: ";
    msg << value;
    controller->getContext()->logger->logDebug(msg);

    if (channel == -1) {
        controller->setGlobalValue(type, value);
    } else {
        controller->setChannelValue(channel, type, value);
    }
}

}; // namespace
