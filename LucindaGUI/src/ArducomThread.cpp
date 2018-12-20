#include "Communication.h"

#include "ArducomThread.h"
#include "Logger.h"

#include <exception>
#include <wx/tokenzr.h>

namespace APP_NAMESPACE {

ArducomThread::QueueMessage::QueueMessage() {}

ArducomThread::QueueMessage::QueueMessage(const MessageType type) {
    this->type = type;
}

// Joinable: do not automatically delete itself after termination
ArducomThread::ArducomThread(Communication* comm) : wxThread(wxTHREAD_JOINABLE)
{
    this->comm = comm;
    arducom = nullptr;
    setStatus(DEVICE_INACTIVE);
}

ArducomThread::~ArducomThread()
{
    if (arducom != nullptr)
        delete arducom;
}

bool ArducomThread::setParameters(const wxString& parameters)
{
    deviceInfo.parameters = parameters;
    deviceInfo.name = "<Unknown>";

    // split parameters and convert to vector of std::string
    std::vector<std::string> parArgs;
    parArgs.push_back(std::string());
    wxArrayString parts = wxStringTokenize(parameters);
    auto end = parts.end();
    for (auto part = parts.begin(); part != end; ++part) {
        wxString str = *part;
        parArgs.push_back(std::string(str.mb_str()));
    }

    // validate parameters
    try {
        // parse arguments
        params.setFromArguments(parArgs);
        deviceInfo.address = wxString(params.device);
        if (params.deviceAddress != 0)
            deviceInfo.address << ":" << params.deviceAddress;
        // get a transport object from the parameters
        ArducomMasterTransport* transport = params.validate();
        arducom = new ArducomMaster(transport);
    } catch (const std::exception& e) {
        wxString msg(arducom->getExceptionMessage(e));
        comm->getContext()->logger->logError(msg);
        deviceInfo.info = "Unable to initialize the connection";
        deviceInfo.statusCode = DEVICE_ERROR_CONNECTING;
        deviceInfo.status = msg;
        return false;
    }

    return true;
}

void ArducomThread::connect()
{
    QueueMessage message(MessageType::CONNECT);
    queue.enqueue(message);
}

void ArducomThread::terminate()
{
    if (IsRunning()) {
        QueueMessage message(MessageType::TERMINATE);
        queue.enqueue(message);
    }
}

wxString ArducomThread::getStatusText(DeviceStatus status)
{
    return DeviceInfo::getStatusText(status);
}

DeviceStatus ArducomThread::getStatus(wxString* message)
{
    wxCriticalSectionLocker enter(criticalSection);

    message->Clear();
    message->Append(deviceInfo.status);
    return deviceInfo.statusCode;
}

void ArducomThread::setStatus(DeviceStatus status, const wxString& message)
{
    deviceInfo.statusCode = status;
    deviceInfo.status = getStatusText(status);

    if (status == DEVICE_NOT_CONNECTED) {
        deviceInfo.name = "<unknown>";
        deviceInfo.uptime = 0;
        deviceInfo.flags = 0;
        deviceInfo.freeMem = 0;
    }
    // generate log message
    wxString msg = "Device at ";
    msg << (deviceInfo.address != "" ? deviceInfo.address : "<unknown>") << ": ";
    msg << deviceInfo.status;

    // log with priority depending on status
    switch (status) {
    case DEVICE_INACTIVE: break;
    case DEVICE_NOT_CONNECTED: comm->getContext()->logger->logDebug(msg); break;
    case DEVICE_CONNECTING:  comm->getContext()->logger->logInfo(msg); break;
    case DEVICE_ERROR_CONNECTING: comm->getContext()->logger->logError(msg); break;
    case DEVICE_READY: comm->getContext()->logger->logDebug(msg); break;
    case DEVICE_DISCONNECTING: comm->getContext()->logger->logInfo(msg); break;
    case DEVICE_ERROR: comm->getContext()->logger->logError(msg); break;
    case DEVICE_RECONNECTING: comm->getContext()->logger->logInfo(msg); break;
    case DEVICE_TERMINATED: comm->getContext()->logger->logDebug(msg); break;
    }

    wxCriticalSectionLocker enter(criticalSection);

    // inform communication that status has changed
    comm->update(this);
}

bool ArducomThread::canSend() {
    return (IsRunning() && deviceInfo.statusCode == DEVICE_READY);
}


void ArducomThread::send1ByteCommand(uint8_t command, uint8_t data, bool replacable)
{
    if (canSend()) {
        bool replaced = false;
        if (replacable) {
            // check queue for the same command up to the next boundary
            std::vector<QueueMessage> buffer;
            QueueMessage message;
            while (queue.try_dequeue(message)) {
                if (message.isBoundary)
                    break;
                // replaceable message?
                if (message.command == command) {
                    // replace data
                    message.data[0] = data;
                    replaced = true;
                    break;
                }
                // store message in buffer
                buffer.push_back(message);
            }
            // add buffered messages again
            auto rend = buffer.rend();
            for (auto iter = buffer.rbegin(); iter != rend; ++iter) {
                queue.enqueue(*iter);
            }
        }
        if (!replaced) {
            QueueMessage message(MessageType::SEND_COMMAND);
            message.command = command;
            message.dataLength = 1;
            message.data[0] = data;
            message.isBoundary = !replacable;
            queue.enqueue(message);
        }
    }
}

void ArducomThread::send2ByteCommand(uint8_t command, uint16_t data, bool replacable)
{
    if (canSend()) {
        bool replaced = false;
        if (replacable) {
            // check queue for the same command up to the next boundary
            std::vector<QueueMessage> buffer;
            QueueMessage message;
            while (queue.try_dequeue(message)) {
                if (message.isBoundary)
                    break;
                // replaceable message?
                if (message.command == command) {
                    // replace data
                    message.data[0] = data % 256;
                    message.data[1] = data / 256;
                    replaced = true;
                    break;
                }
                // store message in buffer
                buffer.push_back(message);
            }
            // add buffered messages again
            auto rend = buffer.rend();
            for (auto iter = buffer.rbegin(); iter != rend; ++iter) {
                queue.enqueue(*iter);
            }
        }
        if (!replaced) {
            QueueMessage message(MessageType::SEND_COMMAND);
            message.command = command;
            message.dataLength = 2;
            message.data[0] = data % 256;
            message.data[1] = data / 256;
            message.isBoundary = !replacable;
            queue.enqueue(message);
        }
    }
}

void ArducomThread::send2ByteCommand(uint8_t command, uint8_t data1, uint8_t data2, bool replacable)
{
    if (canSend()) {
        bool replaced = false;
        if (replacable) {
            // check queue for the same command up to the next boundary
            std::vector<QueueMessage> buffer;
            QueueMessage message;
            while (queue.try_dequeue(message)) {
                if (message.isBoundary)
                    break;
                // replaceable message?
                if (message.command == command && message.data[0] == data1) {
                    // replace data
                    message.data[1] = data2;
                    replaced = true;
                    break;
                }
                // store message in buffer
                buffer.push_back(message);
            }
            // add buffered messages again
            auto rend = buffer.rend();
            for (auto iter = buffer.rbegin(); iter != rend; ++iter) {
                queue.enqueue(*iter);
            }
        }
        if (!replaced) {
            QueueMessage message(MessageType::SEND_COMMAND);
            message.command = command;
            message.dataLength = 2;
            message.data[0] = data1;
            message.data[1] = data2;
            message.isBoundary = !replacable;
            queue.enqueue(message);
        }
    }
}

void ArducomThread::send3ByteCommand(uint8_t command, uint8_t data1, uint16_t data2, bool replacable)
{
    if (canSend()) {
        bool replaced = false;
        if (replacable) {
            // check queue for the same command up to the next boundary
            std::vector<QueueMessage> buffer;
            QueueMessage message;
            while (queue.try_dequeue(message)) {
                if (message.isBoundary)
                    break;
                // replaceable message?
                if (message.command == command && message.data[0] == data1) {
                    // replace data
                    message.data[1] = data2 % 256;
                    message.data[2] = data2 / 256;
                    replaced = true;
                    break;
                }
                // store message in buffer
                buffer.push_back(message);
            }
            // add buffered messages again
            auto rend = buffer.rend();
            for (auto iter = buffer.rbegin(); iter != rend; ++iter) {
                queue.enqueue(*iter);
            }
        }
        if (!replaced) {
            QueueMessage message(MessageType::SEND_COMMAND);
            message.command = command;
            message.dataLength = 3;
            message.data[0] = data1;
            message.data[1] = data2 % 256;
            message.data[2] = data2 / 256;
            message.isBoundary = !replacable;
            queue.enqueue(message);
        }
    }
}

void ArducomThread::sendMultiByteCommand(uint8_t command, uint16_t data)
{

}

void ArducomThread::reconnect()
{
    setStatus(DEVICE_RECONNECTING);
    // clear the queue
    while (queue.pop());

    queue.enqueue(QueueMessage(MessageType::DISCONNECT));
    queue.enqueue(QueueMessage(MessageType::CONNECT));
}

wxThread::ExitCode ArducomThread::Entry()
{
    uint8_t destBuffer[ARDUCOM_BUFFERSIZE];
    uint8_t error;

    while (true) {
        QueueMessage message;
        queue.wait_dequeue(message);

        switch (message.type) {
        case MessageType::CONNECT: {
            // clear the queue
            while (queue.pop());
            wxString msg("Connecting to ");
            msg.append(params.device);
            setStatus(DEVICE_CONNECTING, msg);
            // fall through to REFRESH
        }
        case MessageType::REFRESH: {
            uint8_t buffer[ARDUCOM_BUFFERSIZE];
            uint8_t size = 0;
            try {
                // execute version command
                arducom->execute(params, ARDUCOM_VERSION_COMMAND, &(buffer[0]), &size, ARDUCOM_BUFFERSIZE, &(destBuffer[0]), &error);
                // analyze result
#ifdef WIN32
                #pragma pack(1)
				struct
#else
				struct __attribute__((packed))
#endif
					VersionInfo {
					uint8_t version;
					uint32_t uptime;
					uint8_t flags;
					uint16_t freeRAM;
					char info[64];
				} versionInfo;
#ifdef WIN32
				#pragma pack(0)
#endif
                // ensure
				// clear structure
				memset(&versionInfo, 0, sizeof(versionInfo));
				// copy received data
				memcpy(&versionInfo, destBuffer, size);
				wxString info;
				if (versionInfo.version != 1)
                    throw std::runtime_error("Unsupported Arducom version or not an Arducom device");
                if (strcmp(versionInfo.info, "Lucinda v2") != 0)
                    throw std::runtime_error("Unsupported device version or not a compatible device");

                deviceInfo.name = versionInfo.info;
                deviceInfo.uptime = versionInfo.uptime;
                deviceInfo.flags = versionInfo.flags;
                deviceInfo.freeMem = versionInfo.freeRAM;

                setStatus(DEVICE_READY, wxString(versionInfo.info));
            } catch (const std::exception& e) {
                setStatus(DEVICE_NOT_CONNECTED, arducom->getExceptionMessage(e));
            }
            break;
        }
        case MessageType::SEND_COMMAND: {
            if (deviceInfo.statusCode == DEVICE_READY) {
                wxString msg("Sending data to ");
                msg.append(params.device);
                comm->getContext()->logger->logDebug(msg);
                try {
                    // execute command
                    arducom->execute(params, message.command, &(message.data[0]), &message.dataLength, ARDUCOM_BUFFERSIZE, &(destBuffer[0]), &error);
                } catch (const Arducom::FunctionError& e) {
                    // this is a programming error, simply log it
                    comm->getContext()->logger->logError(arducom->getExceptionMessage(e));
                } catch (const std::exception& e) {
                    // other errors are more serious, reconnect to the device
                    setStatus(DEVICE_ERROR, arducom->getExceptionMessage(e));
                    reconnect();
                }
            }
            break;
        }
        case MessageType::DISCONNECT: {
            wxString msg("Disconnecting from ");
            msg.append(params.device);
            comm->getContext()->logger->logDebug(msg);
            try {
                arducom->close(false);
                setStatus(DEVICE_TERMINATED, "");
            } catch (const std::exception& e) {
                setStatus(DEVICE_ERROR, arducom->getExceptionMessage(e));
            }
            break;
        }
        case MessageType::TERMINATE: {
            if (deviceInfo.statusCode == DEVICE_READY) {
                wxString msg("Terminating connection to ");
                msg.append(params.device);
                comm->getContext()->logger->logDebug(msg);

                try {
                    arducom->close(false);
                } catch (const std::exception& e) {
                    comm->getContext()->logger->logDebug(msg);
                }
            }
            setStatus(DEVICE_TERMINATED, "");
            // end thread processing
            return 0;
        }
        }
    }
}

}; // namespace
