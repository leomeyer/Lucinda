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

#include "Context.h"
#include "Configuration.h"
#include "ChannelPanel.h"
#include "GlobalChannelPanel.h"
#include "RegularChannelPanel.h"

#include "ApplicationController.h"

namespace APP_NAMESPACE {

static const wxString CFG_AUI_PERSPECTIVE = wxT("gui");

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
    minimumLogPriority = Logger::LogPriority::LOG_DEBUG;
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
    contentSizer->Add(globalPanel, 0, wxALL, 5);

    RegularChannelPanel* regPanel = new RegularChannelPanel(pContent, appController->getProcessor(), 1);
    contentSizer->Add(regPanel, 0, wxALL, 5);

    regPanel = new RegularChannelPanel(pContent, appController->getProcessor(), 2);
    contentSizer->Add(regPanel, 0, wxALL, 5);


    /*
    // create GUI elements
    ChannelPanel* panel = new ChannelPanel(pContent, appController->getProcessor(), "Test", 0);
    panel->addSlider("Testslider", 0, 100);
    bContentSizer->Add(panel, 0, wxALL|wxEXPAND, 5);


*/

}

void MainGUIFrame::insertLogMessage(const Logger::LogMessage& message) {
    // filter by priority
    if (message.priority < minimumLogPriority)
        return;

    if (logGrid->InsertRows()) {
        wxString sTime = message.datetime.FormatISOTime();
        sTime << "." << message.datetime.GetMillisecond();
        logGrid->SetCellValue(0, 0, sTime);
        switch (message.priority) {
        case Logger::LogPriority::LOG_DEBUG:
            logGrid->SetCellValue(0, 1, "DEBUG");
            break;
        case Logger::LogPriority::LOG_INFO:
            logGrid->SetCellValue(0, 1, "INFO");
            break;
        case Logger::LogPriority::LOG_WARNING:
            logGrid->SetCellValue(0, 1, "WARNING");
            logGrid->SetCellBackgroundColour(0, 1, *wxYELLOW);
            break;
        case Logger::LogPriority::LOG_ERROR:
            logGrid->SetCellValue(0, 1, "ERROR");
            logGrid->SetCellBackgroundColour(0, 1, *wxRED);
            break;
        }
        logGrid->SetCellValue(0, 2, message.text);
    }
}

void MainGUIFrame::setStatusText(const wxString& statusText)
{
    statusBar->SetStatusText(statusText);
}

void MainGUIFrame::updateDeviceInfos(const wxVector<DeviceInfo>& deviceInfos)
{
    deviceGrid->ClearGrid();
    auto end = deviceInfos.end();
    int row = 0;
    for (auto iter = deviceInfos.begin(); iter != end; ++iter) {
        deviceGrid->SetCellValue(row, 0, (*iter).address);
        deviceGrid->SetCellValue(row, 1, (*iter).status);
        deviceGrid->SetCellValue(row, 2, (*iter).name);
        deviceGrid->SetCellValue(row, 3, (*iter).info);
        if ((*iter).freeMem > 0) {
            wxString mem;
            mem << (*iter).freeMem;
            deviceGrid->SetCellValue(row, 4, mem);
        } else
            deviceGrid->SetCellValue(row, 4, "");
        if ((*iter).uptime > 0) {
            wxString uptime;
            uptime << (*iter).uptime;
            deviceGrid->SetCellValue(row, 5, uptime);
        } else
            deviceGrid->SetCellValue(row, 5, "");
        deviceGrid->SetCellValue(row, 6, (*iter).parameters);
    }
}

void MainGUIFrame::OnShow(wxShowEvent& event)
{
/*
    // load perspective
    wxString auiPerspective;
    if (appController->getContext()->config->getString(CFG_AUI_PERSPECTIVE, "Perspective", "", &auiPerspective)) {
        if (auiPerspective != "")
            m_mgr.LoadPerspective(auiPerspective, true);
    }
*/
}

void MainGUIFrame::OnClose(wxCloseEvent &event)
{
    updateTimer->Stop();
    // shut down all dependent threads
    appController->shutdown();

    wxString auiPerspective = m_mgr.SavePerspective();
    appController->getContext()->config->setString(CFG_AUI_PERSPECTIVE, "Perspective", auiPerspective);

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
    // log panel not floating (docked off)?
    if (!m_mgr.GetPane(pLog).IsFloating()) {
        // adjust log grid size
        logGrid->SetSize(event.GetSize());
        // adjust message column width
        int newCol3Size = logGrid->GetSize().x - logGrid->GetColSize(0) - logGrid->GetColSize(1) - 20;
        if (newCol3Size > 0)
            logGrid->SetColSize(2, newCol3Size);
    }
}

void MainGUIFrame::OnDevicePanelSize(wxSizeEvent& event)
{
    // log panel not floating (docked off)?
    if (!m_mgr.GetPane(pDevices).IsFloating()) {
        // adjust log grid size
        deviceGrid->SetSize(event.GetSize());
        // adjust message column width
//        int newCol3Size = logGrid->GetSize().x - logGrid->GetColSize(0) - logGrid->GetColSize(1) - 20;
//        if (newCol3Size > 0)
//            logGrid->SetColSize(2, newCol3Size);
    }
}
}; // namespace
