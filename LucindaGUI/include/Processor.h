#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "GlobalDefines.h"

#include <wx/wx.h>

namespace APP_NAMESPACE {

class Controller;
struct ChannelSettings;
class ChannelPanel;

// This class is the base class for all events.
class SequenceEvent {
protected:
    long eventID;

    SequenceEvent* prev;
    SequenceEvent* next;

public:
    SequenceEvent();
    // This destructor deletes the node to the right
    // effectively destroying all of the remaining events in prev to next order.
    ~SequenceEvent();

    // This method returns the event time and, if necessary, increases time to the next event.
    virtual wxString getTime(long& time);
    virtual wxString getName() = 0;
    virtual wxString getData() = 0;
};

// This class defines an event that does nothing but wait for some time.
class WaitEvent: SequenceEvent {
protected:
    int waitTime;
public:
    virtual wxString getTime(long& time);
    virtual wxString getName();
    virtual wxString getData();

};

// This class defines an event that changes device state.
class DeviceEvent: SequenceEvent {
protected:
    wxString name;
    wxString data;
public:
    virtual wxString getName();
    virtual wxString getData();
};



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
