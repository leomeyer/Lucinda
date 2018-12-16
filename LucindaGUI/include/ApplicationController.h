#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "Communication.h"
#include "../MainGUIFrame.h"

namespace APP_NAMESPACE {

/** The application controller connects application logic and GUI. */
class ApplicationController
{
    public:
        ApplicationController(Communication* comm, MainGUIFrame* frame);
        virtual ~ApplicationController();

        /** Starts the application logic. */
        void start();

        void shutdown();

        // called by the main frame
        void OnUpdateTimer(wxTimerEvent& event);

    protected:
        Communication* comm;
        MainGUIFrame* frame;

    private:
};

}; // namespace

#endif // APPLICATIONCONTROLLER_H
