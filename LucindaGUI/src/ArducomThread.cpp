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

ArducomThread::ArducomThread(Communication* comm)
{
    this->comm = comm;
    arducom = nullptr;
    setStatus(ARD_INACTIVE);
}

ArducomThread::~ArducomThread()
{
    if (arducom != nullptr)
        delete arducom;
}

wxString ArducomThread::DeviceInfo::toString()
{
    wxString result(name);

    result << "; Uptime: ";
    int s = uptime / 1000;
    int m = s / 60;
    int h = m / 60;
    int d = h / 24;
    s = s % 60;
    m = m % 60;
    h = h % 24;
    if ((d > 0) || (h > 0) || (m > 0)) {
        if (d > 0)
            result << d << "d ";
        if ((d > 0) || (h > 0))
            result << h << "h ";
        if ((d > 0) || (h > 0) || (m > 0))
            result << m << "m ";
        result << s << "s";
    }

    result << "; Free RAM: ";
    result << freeMem;

    result << " bytes; Flags: " << flags << (flags & 1 ? " (debug on)" : " (debug off)");

    return result;
}

bool ArducomThread::setParameters(const wxString& parameters)
{
    // get a transport object from the parameters

    // split parameters and convert to vector of std::string
    std::vector<std::string> parArgs;
    parArgs.push_back(std::string());
    wxArrayString parts = wxStringTokenize(parameters);
    auto end = parts.end();
    for (auto part = parts.begin(); part != end; ++part) {
        wxString str = *part;
        parArgs.push_back(std::string(str.mb_str()));
    }

    // parse arguments
    params.setFromArguments(parArgs);

    // validate parameters
    try {
        ArducomMasterTransport* transport = params.validate();
        arducom = new ArducomMaster(transport);
    } catch (const std::exception& e) {
        wxString msg(arducom->getExceptionMessage(e));
        std::cout << msg << std::endl;
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

ArducomThread::Status ArducomThread::getStatus(wxString* message)
{
    wxCriticalSectionLocker enter(criticalSection);

    message->Clear();
    message->Append(this->statusMessage);
    return status;
}

void ArducomThread::setStatus(Status status, const wxString& message)
{
    // generate log message
    wxString msg = "Arducom thread for ";
    msg << (params.device != "" ? params.device : "<unknown>") << ": ";

    switch (status) {
    case ARD_INACTIVE: msg << "Inactive" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_NOT_CONNECTED: msg << "Not connected" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_CONNECTING:  msg << "Connecting" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_ERROR_CONNECTING: msg << "Error connecting" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_READY: msg << "Ready" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_DISCONNECTING: msg << "Disconnecting" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_ERROR: msg << "Error" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    case ARD_TERMINATED: msg << "Terminated" << (message != "" ? " (" : "") << (message != "" ? message : "") << (message != "" ? ")" : ""); break;
    }

    switch (status) {
    case ARD_INACTIVE: comm->getContext()->logger->logDebug(msg); break;
    case ARD_NOT_CONNECTED: comm->getContext()->logger->logDebug(msg); break;
    case ARD_CONNECTING:  comm->getContext()->logger->logInfo(msg); break;
    case ARD_ERROR_CONNECTING: comm->getContext()->logger->logError(msg); break;
    case ARD_READY: comm->getContext()->logger->logInfo(msg); break;
    case ARD_DISCONNECTING: comm->getContext()->logger->logInfo(msg); break;
    case ARD_ERROR: comm->getContext()->logger->logError(msg); break;
    case ARD_TERMINATED: comm->getContext()->logger->logDebug(msg); break;
    }

    wxCriticalSectionLocker enter(criticalSection);

    this->status = status;
    this->statusMessage = message;

    // inform communication that status has changed
    comm->update(this);
}

wxThread::ExitCode ArducomThread::Entry()
{
    uint8_t buffer[ARDUCOM_BUFFERSIZE];
    uint8_t size = 0;
    uint8_t destBuffer[ARDUCOM_BUFFERSIZE];
    uint8_t error;

    while (true) {
        QueueMessage message;
        queue.wait_dequeue(message);

        switch (message.type) {
        case MessageType::CONNECT: {
            wxString msg("Connecting to ");
            msg.append(params.device);
            setStatus(ARD_CONNECTING, msg);
            try {
                arducom->execute(params, 0, &(buffer[0]), &size, ARDUCOM_BUFFERSIZE, &(destBuffer[0]), &error);
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

                setStatus(ARD_READY, wxString(versionInfo.info));
            } catch (const std::exception& e) {
                setStatus(ARD_NOT_CONNECTED, arducom->getExceptionMessage(e));
            }
            break;
        }
        case MessageType::TERMINATE: {
            if (status == ARD_READY) {
                wxString msg("Terminating connection to ");
                msg.append(params.device);
                setStatus(ARD_DISCONNECTING, msg);

                try {
                    arducom->close(false);
                } catch (const std::exception& e) {
                    setStatus(ARD_ERROR, arducom->getExceptionMessage(e));
                }
            }
            setStatus(ARD_TERMINATED, "");
            // end thread processing
            return 0;
        }
        }
    }
}

}; // namespace
