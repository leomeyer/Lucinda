#ifndef ARDUCOMTHREAD_H
#define ARDUCOMTHREAD_H

#include <wx/wx.h>
#include <wx/thread.h>

#include "../Arducom/src/master/ArducomMaster.h"
#include "../Arducom/src/slave/lib/Arducom/Arducom.h"

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
            ARD_DISCONNECTING,
            ARD_ERROR,
            ARD_TERMINATED
        };

        ArducomParameters params;

        DeviceInfo deviceInfo;

        ArducomThread(Communication* comm);
        virtual ~ArducomThread();

        bool setParameters(const wxString& parameters);

        /** Attempt to connect to the device. */
        void connect();

        /** Attempt to terminate the thread. */
        void terminate();

        Status getStatus(wxString* message);

        /** Send a command to the connected device. */
        void send1ByteCommand(uint8_t command, uint8_t data, bool replacable);

        /** Send a command to the connected device. */
        void send2ByteCommand(uint8_t command, uint16_t data, bool replacable);

        void send2ByteCommand(uint8_t command, uint8_t data1, uint8_t data2, bool replacable);

        void send3ByteCommand(uint8_t command, uint8_t data1, uint16_t data2, bool replacable);

        /** Send a command to the connected device. */
        void sendMultiByteCommand(uint8_t command, uint16_t data);


    protected:
        // message types for the message queue
        enum MessageType {
            CONNECT,
            DISCONNECT,
            SEND_COMMAND,
            TERMINATE
        };

        class QueueMessage {

        public:
            MessageType type;
            uint8_t command;
            uint8_t dataLength;
            uint8_t data[ARDUCOM_BUFFERSIZE];
            bool isBoundary;

            QueueMessage();
            QueueMessage(const MessageType type);
        };

        Communication* comm;
        ArducomMaster* arducom;
        wxCriticalSection criticalSection;

        Status status;
        wxString statusMessage;

        BlockingReaderWriterQueue<QueueMessage> queue;

        bool canSend();

        void setStatus(Status status, const wxString& message = "");

        virtual wxThread::ExitCode Entry();

    private:
};

}; // namespace

#endif // ARDUCOMTHREAD_H
