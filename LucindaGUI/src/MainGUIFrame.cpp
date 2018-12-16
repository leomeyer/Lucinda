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
#include "ChannelPanel.h"
#include "GlobalChannelPanel.h"

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
}

MainGUIFrame::~MainGUIFrame()
{
}
void MainGUIFrame::initialize(ApplicationController* appController)
{
    this->appController = appController;

    updateTimer = new wxTimer(this, wxID_ANY);
	Connect(updateTimer->GetId(), wxEVT_TIMER, wxTimerEventHandler(MainGUIFrame::OnUpdateTimer));
    updateTimer->Start(10);

    // create GUI elements
    GlobalChannelPanel* globalPanel = new GlobalChannelPanel(pContent, appController->getProcessor());
    bContentSizer->Add(globalPanel, 0, wxALL|wxEXPAND, 5);

    /*
    // create GUI elements
    ChannelPanel* panel = new ChannelPanel(pContent, appController->getProcessor(), "Test", 0);
    panel->addSlider("Testslider", 0, 100);
    bContentSizer->Add(panel, 0, wxALL|wxEXPAND, 5);
*/
}

void MainGUIFrame::insertLogMessage(const Logger::LogMessage& message) {
    if (logGrid->InsertRows()) {
        wxString sTime = message.datetime.FormatISOTime();
        sTime << "." << message.datetime.GetMillisecond();
        logGrid->SetCellValue(0, 0, sTime);
        logGrid->SetCellValue(0, 1, message.text);
    }
}

void MainGUIFrame::setStatusText(const wxString& statusText)
{
    statusBar->SetStatusText(statusText);
}

void MainGUIFrame::OnClose(wxCloseEvent &event)
{
    updateTimer->Stop();
    // shut down all dependent threads
    appController->shutdown();
    Destroy();
}

void MainGUIFrame::OnQuit(wxCommandEvent &event)
{
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

void MainGUIFrame::OnLogPanelSize(wxSizeEvent& event)
{
    // adjust log grid size
    logGrid->SetSize(event.GetSize());
}

}; // namespace
