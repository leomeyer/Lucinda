#include "ApplicationController.h"

#include "Communication.h"
#include "Processor.h"
#include "Logger.h"

// include for Arducom command numbers
#include "../../commands.h"

namespace APP_NAMESPACE {

ApplicationController::ApplicationController(Context* context, Communication* comm, MainGUIFrame* frame)
{
    this->context = context;
    this->comm = comm;
    this->frame = frame;
}

ApplicationController::~ApplicationController()
{
    //dtor
}

void ApplicationController::start()
{
    lastLogQuery = wxDateTime::UNow();

    comm->loadFromSettings();

    processor = new Processor(this);
}

void ApplicationController::shutdown()
{
    // stop communication
    comm->stop();
}

Processor* ApplicationController::getProcessor()
{
    return processor;
}

Context* ApplicationController::getContext()
{
    return context;
}

void ApplicationController::OnUpdateTimer(wxTimerEvent& event)
{
    // update log
    wxVector<Logger::LogMessage> messages;
    lastLogQuery = context->logger->getMessages(lastLogQuery, messages);

    // insert the messages in reverse order
    for (int i = messages.size() - 1; i >= 0; --i) {
        frame->insertLogMessage(messages[i]);
    }

    /*
    wxString message = comm->getNextMessage();
    if (message != "") {
        frame->setStatusText(message);
    }
    */
}

void ApplicationController::setGlobalValue(SliderType type, int value)
{
    uint8_t commandNumber;
    uint16_t commandValue = (uint16_t)value;

    switch (type) {
        case SLIDER_BRIGHTNESS: {
            commandNumber = ARDUCOM_CMD_SET_GLOBAL_BRIGHTNESS;
            comm->send1ByteCommand(commandNumber, commandValue);
            break;
        }
        default: context->logger->logError("Type of value not recognized"); return;
    }

    // send
}

}; // namespace
