#include "Communication.h"
#include "ArducomThread.h"

#include "Configuration.h"

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
    wxCriticalSectionLocker enter(criticalSection);

    // initialize an ArducomThread for this device
    ArducomThread* thread = new ArducomThread(this);
    if (thread->setParameters(parameters)) {
        // store and start thread
        threads.push_back(thread);
        // start message processing on the thread
        thread->Run();
        // attempt to connect to the device
        thread->connect();
        return thread;
    } else {
        delete thread;
        // the device thread could not be added
        return nullptr;
    }
}

void Communication::loadFromSettings()
{
    long nrOfDevices = context->config->getLong(APPKEY_NR_OF_DEVICES, 0);

    for (long i = 0; i < nrOfDevices; i++) {
        wxString deviceKey(APPKEY_DEVICENAME_PREFIX);
        deviceKey.append("_");
        deviceKey.append(wxString::Format(wxT("%d"), i));
        wxString parameters;
        if (context->config->getString(deviceKey, "", &parameters)) {
            //ArducomThread* thread =
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

wxString Communication::getNextMessage()
{
    UpdateMessage message;
    if (!queue.try_dequeue(message))
        return "";
    ArducomThread* thread = message.thread;
    // return the status message from the thread
    wxString result;
    switch (thread->getStatus(&result)) {
    case ArducomThread::Status::ARD_INACTIVE: return wxString("Inactive");
    case ArducomThread::Status::ARD_NOT_CONNECTED: return wxString("Not connected: ").append(result);
    case ArducomThread::Status::ARD_CONNECTING: return wxString("Connecting to: ").append(thread->params.device);
    case ArducomThread::Status::ARD_ERROR_CONNECTING: return wxString("Connection error: ").append(result);
    case ArducomThread::Status::ARD_READY: return wxString("Ready: ").append(result);
    case ArducomThread::Status::ARD_ERROR: return wxString("Error: ").append(result);
    }
}

void Communication::send1ByteCommand(uint8_t command, uint8_t data)
{
    wxCriticalSectionLocker enter(criticalSection);

    // enqueue command in each thread
    auto end = threads.end();
    for (auto iter = threads.begin(); iter != end; ++iter) {
        (*iter)->send1ByteCommand(command, data);
    }
}


Context* Communication::getContext()
{
    return context;
}


}; // namespace
