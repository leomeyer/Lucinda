#include "ApplicationController.h"

namespace APP_NAMESPACE {

ApplicationController::ApplicationController(Communication* comm, LucindaGUIFrame* frame)
{
    this->comm = comm;
    this->frame = frame;
}

ApplicationController::~ApplicationController()
{
    //dtor
}

void ApplicationController::start()
{
    comm->loadFromSettings();
}

void ApplicationController::OnUpdateTimer(wxTimerEvent& event)
{
    wxString message = comm->getNextMessage();
    if (message != "") {
        frame->setStatusText(message);
    }
}

}; // namespace
