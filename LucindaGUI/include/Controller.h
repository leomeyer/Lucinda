#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <wx/datetime.h>

#include "MainGUIFrame.h"

namespace APP_NAMESPACE {

class Context;
class Communication;
class Processor;
class ChannelPanel;
class UndoManager;

/** The application controller connects application logic and GUI. */
class Controller
{
    public:
        Controller(Context* context, Communication* comm, MainGUIFrame* frame);
        virtual ~Controller();

        /** Starts the application logic. */
        void start();

        void shutdown();

        // called by the main frame
        void OnUpdateTimer(wxTimerEvent& event);

        Processor* getProcessor();

        Context* getContext();

        void setGlobalValue(SliderType type, int value);

        void setChannelValue(uint8_t channel, SliderType type, int value);

        void setChannelSettings(ChannelPanel* panel, bool apply = false);

        void updateUndoState(UndoManager* undoManager);

    protected:
        Context* context;
        Communication* comm;

        MainGUIFrame* frame;

        wxDateTime lastLogQuery;

    private:
};

}; // namespace

#endif // APPLICATIONCONTROLLER_H
