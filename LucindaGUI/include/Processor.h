#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

class ApplicationController;
struct ChannelSettings;
class ChannelPanel;

/** The processor class is the central instance for handling all events that
* change the state of the connected devices. */
class Processor
{
    public:
        Processor(ApplicationController* controller);

        virtual ~Processor();

        void OnValueChange(int channel, SliderType type, int value);

        void OnSetChannelSettings(ChannelPanel* panel);

    protected:
        ApplicationController* controller;

    private:
};

}; // namespace

#endif // PROCESSOR_H
