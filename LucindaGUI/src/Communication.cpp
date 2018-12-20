#include "Communication.h"
#include "ArducomThread.h"

#include "Configuration.h"
#include "Logger.h"

// include for Arducom command numbers
#include "../../commands.h"

namespace APP_NAMESPACE {

Communication::Communication(Context* context)
{
    this->context = context;
}

Communication::~Communication()
{
    //dtor
}

ArducomThread* Communication::addThread(const wxString& parameters) {
    // initialize an ArducomThread for this device
    ArducomThread* thread = new ArducomThread(this);
    // store and start thread
    wxCriticalSectionLocker enter(criticalSection);
    if (thread->setParameters(parameters)) {
        // attempt to connect to the device
        thread->connect();
    } else {
        thread->deviceInfo.info = "Parameters invalid";
    }
    // check whether the address is already present
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        if ((*iter)->deviceInfo.address == thread->deviceInfo.address) {
            // already there, do not add
            delete thread;
            return nullptr;
        }
    }
    threads.push_back(thread);
    thread->Run();
    return thread;
}

void Communication::loadFromSettings()
{
    wxString msg = "Loading configuration from: ";
    msg << context->config->getOrigin();
    context->logger->logDebug(msg);

    long nrOfDevices = context->config->getLong(APPKEY_NR_OF_DEVICES, 0);

    for (long i = 0; i < nrOfDevices; i++) {
        wxString deviceKey(APPKEY_DEVICENAME_PREFIX);
        deviceKey.append("_");
        deviceKey.append(wxString::Format(wxT("%d"), i));
        wxString parameters;
        if (context->config->getString(deviceKey, "", &parameters)) {
            msg = "Initializing ";
            msg << deviceKey << ": " << parameters;
            context->logger->logDebug(msg);

            addThread(parameters);
        }
    }
}

void Communication::stop()
{
    wxCriticalSectionLocker enter(criticalSection);

    // tell each thread to terminate
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->terminate();
        // wait for termination with timeout
        int i = 1000;
        while ((*iter)->IsRunning()) {
            Sleep(1);   // sleep for a millisecond
            i--;
            if (i < 0) break;
        }
        if (i < 0)
            // kill the thread hard
            (*iter)->Kill();
        delete *iter;
    }
    threads.clear();
}


Communication::UpdateMessage::UpdateMessage() {}

Communication::UpdateMessage::UpdateMessage(ArducomThread* thread)
{
    this->thread = thread;
}

void Communication::update(ArducomThread* thread)
{
    UpdateMessage message(thread);
    queue.enqueue(message);
}

wxString Communication::getThreadStatus(ArducomThread* thread) {
    // return the status message from the thread
    wxString result;
    switch (thread->getStatus(&result)) {
    case DeviceStatus::DEVICE_INACTIVE: return wxString("Inactive");
    case DeviceStatus::DEVICE_NOT_CONNECTED: return wxString("Not connected: ").append(result);
    case DeviceStatus::DEVICE_CONNECTING: return wxString("Connecting to: ").append(thread->params.device);
    case DeviceStatus::DEVICE_ERROR_CONNECTING: return wxString("Connection error: ").append(result);
    case DeviceStatus::DEVICE_READY: return wxString("Ready: ").append(result);
    case DeviceStatus::DEVICE_ERROR: return wxString("Error: ").append(result);
    }
    return result;
}

Context* Communication::getContext()
{
    return context;
}

void Communication::getDeviceInfos(wxVector<DeviceInfo>& deviceInfos)
{
    deviceInfos.clear();

    wxCriticalSectionLocker enter(criticalSection);
    // get current device infos from threads
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        DeviceInfo deviceInfo = (*iter)->deviceInfo;
        deviceInfo.info = getThreadStatus(*iter);
        deviceInfos.push_back(deviceInfo);
    }
}

// device commands
void Communication::defineChannel()
{

}

void Communication::setGlobalSpeed(uint8_t speed)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send1ByteCommand(ARDUCOM_CMD_SET_GLOBAL_SPEED, speed, true);
    }
}

void Communication::setGlobalBrightness(uint8_t brightness)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send1ByteCommand(ARDUCOM_CMD_SET_GLOBAL_BRIGHTNESS, brightness, true);
    }
}

void Communication::enableChannel(uint8_t channel)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send1ByteCommand(ARDUCOM_CMD_ENABLE_CHANNEL, channel, false);
    }
}

void Communication::disableChannel(uint8_t channel)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send1ByteCommand(ARDUCOM_CMD_DISABLE_CHANNEL, channel, false);
    }
}

void Communication::setChannelPeriod(uint8_t channel, uint16_t period)
{
   wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send3ByteCommand(ARDUCOM_CMD_SET_CHANNEL_PERIOD, channel, period, true);
    }
}

void Communication::setChannelPhaseShift(uint8_t channel, uint8_t phaseshift)
{
   wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send2ByteCommand(ARDUCOM_CMD_SET_CHANNEL_PHASESHIFT, channel, phaseshift, true);
    }
}

void Communication::setChannelOffset(uint8_t channel, uint8_t offset)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send2ByteCommand(ARDUCOM_CMD_SET_CHANNEL_OFFSET, channel, offset, true);
    }
}

void Communication::setChannelBrightness(uint8_t channel, uint8_t brightness)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send2ByteCommand(ARDUCOM_CMD_SET_CHANNEL_BRIGHTNESS, channel, brightness, true);
    }
}

void Communication::setChannelDutyCycle(uint8_t channel, uint8_t dutycycle)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send2ByteCommand(ARDUCOM_CMD_SET_CHANNEL_DUTYCYCLE, channel, dutycycle, true);
    }

}



}; // namespace
