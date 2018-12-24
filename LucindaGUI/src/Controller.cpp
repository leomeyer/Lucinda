#include "Controller.h"

#include "Communication.h"
#include "Processor.h"
#include "Logger.h"
#include "DeviceInfo.h"
#include "ChannelPanel.h"
#include "UndoManager.h"

namespace APP_NAMESPACE {

Controller::Controller(Context* context, Communication* comm, MainGUIFrame* frame)
{
    this->context = context;
    this->comm = comm;
    this->frame = frame;
}

Controller::~Controller()
{
    //dtor
}

void Controller::start()
{
    context->logger->logInfo("Application startup.");

    lastLogQuery = wxDateTime::UNow();

    context->processor = new Processor(this);
    context->undoManager = new UndoManager(this);

    comm->loadFromSettings();
}

void Controller::shutdown()
{
    // stop communication
    comm->stop();
}

Processor* Controller::getProcessor()
{
    return context->processor;
}

Context* Controller::getContext()
{
    return context;
}

void Controller::OnUpdateTimer(wxTimerEvent& event)
{
    // update device info
    wxVector<DeviceInfo> deviceInfos;
    comm->getDeviceInfos(deviceInfos);
    frame->updateDeviceInfos(deviceInfos);

    // update log
    wxVector<Logger::LogMessage> messages;
    lastLogQuery = context->logger->getMessages(lastLogQuery, messages);

    // insert the messages in reverse order
    for (int i = messages.size() - 1; i >= 0; --i) {
        frame->insertLogMessage(messages[i]);
    }
}

void Controller::setGlobalValue(SliderType type, int value)
{
    switch (type) {
        case SLIDER_BRIGHTNESS: {
            comm->setGlobalBrightness((uint8_t)value);
            break;
        }
        case SLIDER_GLOBAL_SPEED: {
            comm->setGlobalSpeed((uint8_t)value);
            break;
        }
        default: context->logger->logError("Type of slider not recognized"); return;
    }
}

void Controller::setChannelValue(uint8_t channel, SliderType type, int value)
{
    switch (type) {
        case SLIDER_PERIOD: {
            comm->setChannelPeriod(channel, (uint16_t)value);
            break;
        }
        case SLIDER_PHASESHIFT: {
            comm->setChannelPhaseShift(channel, (uint16_t)value);
            break;
        }
        case SLIDER_BRIGHTNESS: {
            comm->setChannelBrightness(channel, (uint8_t)value);
            break;
        }
        case SLIDER_OFFSET: {
            comm->setChannelOffset(channel, (uint8_t)value);
            break;
        }
        case SLIDER_DUTYCYCLE: {
            comm->setChannelDutyCycle(channel, (uint8_t)value);
            break;
        }
        default: context->logger->logError("Type of slider not recognized"); return;
    }
}

void Controller::setChannelSettings(ChannelPanel* panel, bool apply)
{
    comm->setChannelSettings(
        panel->getChannel(),
        panel->getSettings()->enabled,
        panel->getSettings()->getDeviceBitmask(),
        panel->getPeriod(),
        panel->getOffset(),
        panel->getBrightness(),
        panel->getDutyCycle(),
        panel->getPhaseshift(),
        panel->getSettings()->waveform,
        panel->getSettings()->eyeCorrection,
        panel->getSettings()->invert,
        panel->getSettings()->reverse,
        panel->getSettings()->getNoLightsFlag(),
        apply,
        panel->getSettings()->mcLength,
        panel->getSettings()->mcCount,
        panel->getSettings()->mcShift
    );
}

void Controller::updateUndoState(UndoManager* undoManager)
{
    frame->updateUndoState(undoManager);
}


}; // namespace
