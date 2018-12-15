#include "Communication.h"
#include "ArducomThread.h"

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
    if (thread->setParameters(parameters)) {
        // store and start thread
        threads.push_back(thread);
        // start message processing on the thread
        thread->Run();
        // attempt to connect to the device
        thread->connect();
        return thread;
    } else
        // the device thread could not be added
        return nullptr;
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

Communication::UpdateMessage::UpdateMessage()
{
}

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


}; // namespace
