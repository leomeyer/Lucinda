#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <wx/vector.h>

#include "Context.h"
#include "IDeviceCommands.h"
#include "DeviceInfo.h"

#include "readerwriterqueue.h"

namespace APP_NAMESPACE {

using namespace moodycamel;

class ArducomThread;

class Communication: IDeviceCommands
{
    public:
        Communication(Context* context);
        virtual ~Communication();

        void loadFromSettings();

        void stop();

        /** Tells the communication class that something has changed about this thread. */
        void update(ArducomThread* thread);

        Context* getContext();

        wxString getThreadStatus(ArducomThread* thread);

        void getDeviceInfos(wxVector<DeviceInfo>& deviceInfos);

        // Implementations of device commands
        virtual void setChannelSettings(
            int channel,
            bool enabled,
            uint8_t bitmask,
            uint16_t period,
            uint8_t offset,
            uint8_t brightness,
            uint8_t dutycycle,
            uint8_t phaseshift,
            uint8_t waveform,
            bool eyeCorrection,
            bool invert,
            bool reverse,
            bool noLights,
            bool apply,
            uint8_t mcCount,
            uint8_t mcLength,
            uint8_t mcShift
        );

        virtual void setGlobalSpeed(uint8_t speed);

        virtual void setGlobalBrightness(uint8_t brightness);

        virtual void enableChannel(uint8_t channel);

        virtual void disableChannel(uint8_t channel);

        virtual void setChannelPeriod(uint8_t channel, uint16_t period);

        virtual void setChannelPhaseShift(uint8_t channel, uint8_t phaseshift);

        virtual void setChannelOffset(uint8_t channel, uint8_t offset);

        virtual void setChannelBrightness(uint8_t channel, uint8_t brightness);

        virtual void setChannelDutyCycle(uint8_t channel, uint8_t dutycycle);

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
