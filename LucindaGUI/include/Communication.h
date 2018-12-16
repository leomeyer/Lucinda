#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <wx/vector.h>

#include "Context.h"

#include "readerwriterqueue.h"

namespace APP_NAMESPACE {

using namespace moodycamel;

class ArducomThread;

class Communication
{
    public:
        Communication(Context* context);
        virtual ~Communication();

        void loadFromSettings();

        void stop();

        /** Tells the communication class that something has changed about this thread. */
        void update(ArducomThread* thread);

        /** Retrieves the next message from the queue if available, else an empty string. */
        wxString getNextMessage();

        /** Distribute a command to the connected devices. */


        Context* getContext();

    protected:
        class UpdateMessage {
        public:
            UpdateMessage();
            UpdateMessage(ArducomThread* thread);

            ArducomThread* thread;
        };

        Context* context;
        wxVector<ArducomThread*> threads;
        // threads are protected using a critical section
        wxCriticalSection criticalSection;

        ReaderWriterQueue<UpdateMessage> queue;

        ArducomThread* addThread(const wxString& parameters);

    private:
};

}; // namespace

#endif // COMMUNICATION_H
