#ifndef DEVICECOMMANDS_H_INCLUDED
#define DEVICECOMMANDS_H_INCLUDED

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

// interface for device commands
class IDeviceCommands {

public:
    virtual void defineChannel() = 0;

    virtual void setGlobalSpeed(uint8_t speed) = 0;

    virtual void setGlobalBrightness(uint8_t brightness) = 0;

    virtual void enableChannel(uint8_t channel) = 0;

    virtual void disableChannel(uint8_t channel) = 0;

    virtual void setChannelPeriod(uint8_t channel, uint16_t period) = 0;

    virtual void setChannelPhaseShift(uint8_t channel, uint8_t phaseshift) = 0;

    virtual void setChannelOffset(uint8_t channel, uint8_t offset) = 0;

    virtual void setChannelBrightness(uint8_t channel, uint8_t brightness) = 0;

    virtual void setChannelDutyCycle(uint8_t channel, uint8_t dutycycle) = 0;
};

}; // namespace

#endif // DEVICECOMMANDS_H_INCLUDED
