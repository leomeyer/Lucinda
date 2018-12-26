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

void Controller::addPanel(ChannelPanel* panel)
{
    channelPanels.push_back(panel);
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

void Controller::loadDefaultChannelSettings()
{
    context->undoManager->collect();

    try {
        ChannelSettings settings;
        settings.waveform = WAVEFORM_SINE;
        settings.reverse = false;
        settings.invert = false;
        settings.eyeCorrection = true;
        settings.mcCount = 0;
        settings.mcLength = 0;
        settings.mcShift = 0;
        settings.enabled = true;

        auto end = channelPanels.end();
        for (auto iter = channelPanels.begin(); iter != end; ++iter) {
            if ((*iter)->getChannel() == 0)
                settings.lights = 0;
            else if ((*iter)->getChannel() == 1)
                settings.lights = 5;
            else if ((*iter)->getChannel() == 2)
                settings.lights = 160;
            else if ((*iter)->getChannel() == 3)
                settings.lights = 10;
            else if ((*iter)->getChannel() == 4)
                settings.lights = 80;
            else
                settings.lights = -1;

            (*iter)->setSettings(settings);
        }
        context->undoManager->collectDone();
    } catch (...) {
        context->undoManager->collectDone();
    }
}

void Controller::sendGlobalValue(SliderType type, int value)
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

void Controller::sendChannelValue(uint8_t channel, SliderType type, int value)
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

void Controller::sendChannelSettings(ChannelPanel* panel, bool apply)
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

void Controller::sendAllChannelSettings(bool apply)
{
    auto end = channelPanels.end();
    for (auto iter = channelPanels.begin(); iter != end; ++iter) {
        if ((*iter)->getChannel() >= 0)
            (*iter)->sendSettings(apply);
    }
}

void Controller::synchronize()
{
    // synchronize by setting global speed to 0
    // and then to 1 again after some time
    comm->setGlobalSpeed(0);
    Sleep(100);
    comm->setGlobalSpeed(1);
}

void Controller::updateUndoState(UndoManager* undoManager)
{
    frame->updateUndoState(undoManager);
}


}; // namespace
