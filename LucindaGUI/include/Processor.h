#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

class ApplicationController;

/** The processor class is the central instance for handling all events that
* change the state of the connected devices. */
class Processor
{
    public:
        Processor(ApplicationController* controller);

        virtual ~Processor();

        void OnValueChange(int channel, SliderType type, int value);

    protected:
        ApplicationController* controller;

    private:
};

}; // namespace

#endif // PROCESSOR_H