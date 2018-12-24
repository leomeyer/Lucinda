#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

class Controller;
struct ChannelSettings;
class ChannelPanel;

/** The processor class is the central instance for handling all events that
* change the state of the connected devices. */
class Processor
{
    public:
        Processor(Controller* controller);

        virtual ~Processor();

        void OnValueChange(int channel, SliderType type, int value);

        void OnSendChannelSettings(ChannelPanel* panel, bool apply = false);

    protected:
        Controller* controller;

    private:
};

}; // namespace

#endif // PROCESSOR_H
