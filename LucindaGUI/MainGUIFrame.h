/***************************************************************
 * Name:      MainGUIFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Leo Meyer (leo@leomeyer.de)
 * Created:   2018-12-14
 * Copyright: Leo Meyer ()
 * License:
 **************************************************************/

#ifndef MAINGUIFRAME_H
#define MAINGUIFRAME_H

#include "GlobalDefines.h"
#include "GUIFrame.h"

namespace APP_NAMESPACE {

class ApplicationController;

class MainGUIFrame: public GUIFrame
{
    public:
        MainGUIFrame(wxFrame *frame);
        ~MainGUIFrame();

        void setAppController(ApplicationController* appController);

        void setStatusText(const wxString& statusText);
    private:
        ApplicationController* appController;
        wxTimer* updateTimer;

        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);

        void OnUpdateTimer(wxTimerEvent& event);
    };

}; // namespace

#endif // MAINGUIFRAME_H
