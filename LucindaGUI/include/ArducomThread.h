#ifndef ARDUCOMTHREAD_H
#define ARDUCOMTHREAD_H

#include <wx/wx.h>
#include <wx/thread.h>

#include "../Arducom/src/master/ArducomMaster.h"

#include "readerwriterqueue.h"

namespace APP_NAMESPACE {

using namespace moodycamel;

class Communication;

class ArducomParameters: public ArducomBaseParameters {
    virtual void showVersion(void) {};

    virtual void showHelp(void) {};
};

class ArducomThread : public wxThread
{
    public:

        enum Status {
            ARD_INACTIVE,
            ARD_NOT_CONNECTED,
            ARD_CONNECTING,
            ARD_ERROR_CONNECTING,
            ARD_READY,
            ARD_ERROR
        };

        ArducomParameters params;

        ArducomThread(Communication* comm);
        virtual ~ArducomThread();

        bool setParameters(const wxString& parameters);

        /** Attempt to connect to the device. */
        void connect();

        Status getStatus(wxString* message);

    protected:
        // message types for the message queue
        enum MessageType {
            CONNECT,
            DISCONNECT,
            TERMINATE
        };

        class QueueMessage {

        public:
            MessageType type;
            QueueMessage();
            QueueMessage(const MessageType type);
        };

        Communication* comm;
        ArducomMaster* arducom;
        wxCriticalSection criticalSection;

        Status status;
        wxString statusMessage;

        BlockingReaderWriterQueue<QueueMessage> queue;

        void setStatus(Status status, wxString message);

        virtual wxThread::ExitCode Entry();

    private:
};

}; // namespace

#endif // ARDUCOMTHREAD_H
