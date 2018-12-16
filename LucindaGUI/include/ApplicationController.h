#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <wx/datetime.h>

#include "MainGUIFrame.h"

namespace APP_NAMESPACE {

class Context;
class Communication;
class Processor;

/** The application controller connects application logic and GUI. */
class ApplicationController
{
    public:
        ApplicationController(Context* context, Communication* comm, MainGUIFrame* frame);
        virtual ~ApplicationController();

        /** Starts the application logic. */
        void start();

        void shutdown();

        // called by the main frame
        void OnUpdateTimer(wxTimerEvent& event);

        Processor* getProcessor();

        Context* getContext();

        // Communication methods

        void setGlobalValue(SliderType type, int value);

    protected:
        Context* context;
        Communication* comm;
        Processor* processor;

        MainGUIFrame* frame;

        wxDateTime lastLogQuery;

    private:
};

}; // namespace

#endif // APPLICATIONCONTROLLER_H
