/***************************************************************
 * Name:      MainGUIFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Leo Meyer (leo@leomeyer.de)
 * Created:   2018-12-14
 * Copyright: Leo Meyer ()
 * License:
 **************************************************************/

#include <wx/wx.h>

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MainGUIFrame.h"
#include "ApplicationController.h"

namespace APP_NAMESPACE {

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


MainGUIFrame::MainGUIFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif

    updateTimer = new wxTimer(this, wxID_ANY);
	Connect(updateTimer->GetId(), wxEVT_TIMER, wxTimerEventHandler(MainGUIFrame::OnUpdateTimer));
    updateTimer->Start(10);
}

MainGUIFrame::~MainGUIFrame()
{
}
void MainGUIFrame::setAppController(ApplicationController* appController)
{
    this->appController = appController;
}

void MainGUIFrame::setStatusText(const wxString& statusText)
{
    statusBar->SetStatusText(statusText);
}

void MainGUIFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void MainGUIFrame::OnQuit(wxCommandEvent &event)
{
    updateTimer->Stop();
    // shut down all dependent threads
    appController->shutdown();
    Destroy();
}

void MainGUIFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void MainGUIFrame::OnUpdateTimer(wxTimerEvent& event)
{
    // let application logic update GUI data
    appController->OnUpdateTimer(event);
}

}; // namespace
