#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "Communication.h"
#include "../LucindaGUIMain.h"

namespace APP_NAMESPACE {

/** The application controller connects application logic and GUI. */
class ApplicationController
{
    public:
        ApplicationController(Communication* comm, LucindaGUIFrame* frame);
        virtual ~ApplicationController();

        /** Starts the application logic. */
        void start();

        // called by the main frame
        void OnUpdateTimer(wxTimerEvent& event);

    protected:
        Communication* comm;
        LucindaGUIFrame* frame;

    private:
};

}; // namespace

#endif // APPLICATIONCONTROLLER_H
