/***************************************************************
 * Name:      MainGUIFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Leo Meyer (leo@leomeyer.de)
 * Created:   2018-12-14
 * Copyright: Leo Meyer ()
 * License:
 **************************************************************/

#include <wx/wx.h>
#include <algorithm>

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
#include "DeviceInfo.h"
#include "GlobalChannelPanel.h"
#include "RegularChannelPanel.h"

#include "Controller.h"

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

    tUndo->SetState(wxAUI_BUTTON_STATE_DISABLED);
    tRedo->SetState(wxAUI_BUTTON_STATE_DISABLED);
}

MainGUIFrame::~MainGUIFrame()
{
}

void MainGUIFrame::initialize(Controller* controller)
{
    this->controller = controller;

    updateTimer = new wxTimer(this, wxID_ANY);
	Connect(updateTimer->GetId(), wxEVT_TIMER, wxTimerEventHandler(MainGUIFrame::OnUpdateTimer));
    updateTimer->Start(10);

    // create GUI elements
    GlobalChannelPanel* globalPanel = new GlobalChannelPanel(pChannels, controller);
    channelSizer->Add(globalPanel, 0, wxALL, 5);
    channelPanels.push_back(globalPanel);
    controller->addPanel(globalPanel);

    RegularChannelPanel* regPanel = new RegularChannelPanel(pChannels, controller, 0);
    channelSizer->Add(regPanel, 0, wxALL, 5);
    channelPanels.push_back(regPanel);
    controller->addPanel(regPanel);

    regPanel = new RegularChannelPanel(pChannels, controller, 1);
    channelSizer->Add(regPanel, 0, wxALL, 5);
    channelPanels.push_back(regPanel);
    controller->addPanel(regPanel);

    regPanel = new RegularChannelPanel(pChannels, controller, 2);
    channelSizer->Add(regPanel, 0, wxALL, 5);
    channelPanels.push_back(regPanel);
    controller->addPanel(regPanel);

    regPanel = new RegularChannelPanel(pChannels, controller, 3);
    channelSizer->Add(regPanel, 0, wxALL, 5);
    channelPanels.push_back(regPanel);
    controller->addPanel(regPanel);

    regPanel = new RegularChannelPanel(pChannels, controller, 4);
    channelSizer->Add(regPanel, 0, wxALL, 5);
    channelPanels.push_back(regPanel);
    controller->addPanel(regPanel);

    /*
    // create GUI elements
    ChannelPanel* panel = new ChannelPanel(pContent, controller->getProcessor(), "Test", 0);
    panel->addSlider("Testslider", 0, 100);
    bContentSizer->Add(panel, 0, wxALL|wxEXPAND, 5);


*/

}

void MainGUIFrame::applyGUISettings()
{
    wxSize contentSize = pContent->GetSize();
    int contentSplitterPos = controller->getContext()->config->getLong(SETTING_CONTENT_SPLITTER_POS, contentSize.y / 2);
    contentSplitter->SetSashPosition(contentSplitterPos);
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
            logGrid->SetCellBackgroundColour(0, 1, *wxWHITE);
            break;
        case Logger::LogPriority::LOG_INFO:
            logGrid->SetCellValue(0, 1, "INFO");
            logGrid->SetCellBackgroundColour(0, 1, *wxWHITE);
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
    #define DEV_ADDRESS_COL 0
    #define DEV_STATUS_COL  1
    #define DEV_NAME_COL    2
    #define DEV_MEM_COL     3
    #define DEV_UPTIME_COL  4
    #define DEV_PARAMS_COL  5
    #define DEV_INFO_COL    6

    // need to rebuild?
    if (deviceInfos.size() != (size_t)deviceGrid->GetNumberRows()) {

        deviceGrid->DeleteRows(0, deviceGrid->GetNumberRows());
        auto end = deviceInfos.end();
        for (auto iter = deviceInfos.begin(); iter != end; ++iter) {
            deviceGrid->AppendRows();
            int row = deviceGrid->GetNumberRows() - 1;
            deviceGrid->SetCellValue(row, DEV_ADDRESS_COL, (*iter).address);
            deviceGrid->SetCellValue(row, DEV_STATUS_COL, DeviceInfo::getStatusText((*iter).statusCode));
            deviceGrid->SetCellValue(row, DEV_NAME_COL, (*iter).name);
            deviceGrid->SetCellValue(row, DEV_MEM_COL, (*iter).freeMemStr());
            deviceGrid->SetCellValue(row, DEV_UPTIME_COL, (*iter).uptimeStr());
            deviceGrid->SetCellValue(row, DEV_PARAMS_COL, (*iter).parameters);
            deviceGrid->SetCellValue(row, DEV_INFO_COL, (*iter).info);
            deviceGrid->SetCellBackgroundColour(row, DEV_STATUS_COL, *wxWHITE);
            if ((*iter).statusCode == DEVICE_ERROR_CONNECTING || (*iter).statusCode == DEVICE_ERROR)
                deviceGrid->SetCellBackgroundColour(row, DEV_STATUS_COL, *wxRED);
            else if ((*iter).statusCode == DEVICE_NOT_CONNECTED)
                deviceGrid->SetCellBackgroundColour(row, DEV_STATUS_COL, *wxYELLOW);
        }
    } else {
        auto end = deviceInfos.end();
        wxVector<int> rowsNotHandled;
        for (int i = 0; i < deviceGrid->GetNumberRows(); i++)
            rowsNotHandled.push_back(i);

        for (auto iter = deviceInfos.begin(); iter != end; ++iter) {
            // find row for this address
            int row = -1;
            for (int i = 0; i < deviceGrid->GetNumberRows(); i++) {
                if (deviceGrid->GetCellValue(i, 0) == (*iter).address) {
                    row = i;
                    // remove row from list of unhandled rows
                    rowsNotHandled.erase(std::remove(rowsNotHandled.begin(), rowsNotHandled.end(), row), rowsNotHandled.end());
                    break;
                }
            }
            // row not found?
            if (row == -1) {
                // append the row
                deviceGrid->AppendRows();
                row = deviceGrid->GetNumberRows() - 1;
            }
            // set values only if they have changed to reduce flickering
            if (deviceGrid->GetCellValue(row, DEV_ADDRESS_COL) != (*iter).address)
                deviceGrid->SetCellValue(row, DEV_ADDRESS_COL, (*iter).address);
            if (deviceGrid->GetCellValue(row, DEV_STATUS_COL) != DeviceInfo::getStatusText((*iter).statusCode))
                deviceGrid->SetCellValue(row, DEV_STATUS_COL, DeviceInfo::getStatusText((*iter).statusCode));
            if (deviceGrid->GetCellValue(row, DEV_NAME_COL) != (*iter).name)
                deviceGrid->SetCellValue(row, DEV_NAME_COL, (*iter).name);
            if (deviceGrid->GetCellValue(row, DEV_MEM_COL) != (*iter).freeMemStr())
                deviceGrid->SetCellValue(row, DEV_MEM_COL, (*iter).freeMemStr());
            if (deviceGrid->GetCellValue(row, DEV_UPTIME_COL) != (*iter).uptimeStr())
                deviceGrid->SetCellValue(row, DEV_UPTIME_COL, (*iter).uptimeStr());
            if (deviceGrid->GetCellValue(row, DEV_PARAMS_COL) != (*iter).parameters)
                deviceGrid->SetCellValue(row, DEV_PARAMS_COL, (*iter).parameters);
            if (deviceGrid->GetCellValue(row, DEV_INFO_COL) != (*iter).info)
                deviceGrid->SetCellValue(row, DEV_INFO_COL, (*iter).info);
            deviceGrid->SetCellBackgroundColour(row, DEV_STATUS_COL, *wxWHITE);
            if ((*iter).statusCode == DEVICE_ERROR_CONNECTING || (*iter).statusCode == DEVICE_ERROR)
                deviceGrid->SetCellBackgroundColour(row, DEV_STATUS_COL, *wxRED);
            else if ((*iter).statusCode == DEVICE_NOT_CONNECTED)
                deviceGrid->SetCellBackgroundColour(row, DEV_STATUS_COL, *wxYELLOW);
        }

        // remove unhandled rows
        for (size_t i = 0; i < rowsNotHandled.size(); i++)
            deviceGrid->DeleteRows(rowsNotHandled.at(i));
    }
}

void MainGUIFrame::updateUndoState(UndoManager* undoManager)
{
    // update menu item and toolbar button states
    if (undoManager->canUndo()) {
        miUndo->Enable(true);
        tUndo->SetState(wxAUI_BUTTON_STATE_NORMAL);
        tUndo->SetShortHelp(undoManager->getUndoLabel());
    } else {
        miUndo->Enable(false);
        tUndo->SetState(wxAUI_BUTTON_STATE_DISABLED);
        tUndo->SetShortHelp("Undo");
    }
    if (undoManager->canRedo()) {
        miRedo->Enable(true);
        tRedo->SetState(wxAUI_BUTTON_STATE_NORMAL);
        tRedo->SetShortHelp(undoManager->getRedoLabel());
    } else {
        miRedo->Enable(false);
        tRedo->SetState(wxAUI_BUTTON_STATE_DISABLED);
        tRedo->SetShortHelp("Redo");
    }
    toolbar->Refresh();
}

void MainGUIFrame::OnUndo(wxCommandEvent& event)
{
    controller->getContext()->undoManager->undo();

    updateUndoState(controller->getContext()->undoManager);
}

void MainGUIFrame::OnRedo(wxCommandEvent& event)
{
    controller->getContext()->undoManager->redo();

    updateUndoState(controller->getContext()->undoManager);
}

void MainGUIFrame::OnShow(wxShowEvent& event)
{
    // not called ???
/*
    // load perspective
    wxString auiPerspective;
    if (controller->getContext()->config->getString(CFG_AUI_PERSPECTIVE, "Perspective", "", &auiPerspective)) {
        if (auiPerspective != "")
            m_mgr.LoadPerspective(auiPerspective, true);
    }
*/

    updateUndoState(controller->getContext()->undoManager);
}

void MainGUIFrame::OnClose(wxCloseEvent &event)
{
    updateTimer->Stop();
    // shut down all dependent threads
    controller->shutdown();

    wxString auiPerspective = m_mgr.SavePerspective();
    controller->getContext()->config->setString(CFG_AUI_PERSPECTIVE, "Perspective", auiPerspective);
    controller->getContext()->config->setLong(SETTING_CONTENT_SPLITTER_POS, contentSplitter->GetSashPosition());
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
    controller->OnUpdateTimer(event);
}

void MainGUIFrame::OnSplitterChanging(wxSplitterEvent& event)
{
    // for some reason the trackSplitter also generates these events
    // even though it is not connected
    if (event.GetEventObject() == contentSplitter) {
        auto end = channelPanels.end();
        for (auto iter = channelPanels.begin(); iter != end; ++iter) {
            wxSize size = (*iter)->GetSize();
            size.y = event.GetSashPosition() - 30;
            //size.y = event.GetSize().y - 20;
            (*iter)->SetSize(size);
            (*iter)->SetMinSize(size);
            (*iter)->Layout();
        }
    }
}

void MainGUIFrame::OnSplitterChanged(wxSplitterEvent& event)
{
    // for some reason the trackSplitter also generates these events
    // even though it is not connected
    if (event.GetEventObject() == contentSplitter) {
        auto end = channelPanels.end();
        for (auto iter = channelPanels.begin(); iter != end; ++iter) {
            wxSize size = (*iter)->GetSize();
            size.y = event.GetSashPosition();
            //size.y = event.GetSize().y - 20;
            (*iter)->SetSize(size);
    //        (*iter)->SetSize(size);
    //        (*iter)->Layout();
        }
        pChannels->Layout();
    }
}

void MainGUIFrame::OnChannelsSize(wxSizeEvent& event)
{
    auto end = channelPanels.end();
    for (auto iter = channelPanels.begin(); iter != end; ++iter) {
        wxSize size = event.GetSize();
        //size.y = event.GetSize().y - 20;
        channelSizer->SetMinSize(size);
//        (*iter)->SetSize(size);
//        (*iter)->Layout();
    }
    pChannels->Layout();
}

void MainGUIFrame::expandGrid(wxGrid* grid, const wxSize& size)
{
    // adjust grid size
    grid->SetSize(size);
    int colSizeSum = 0;
    for (int i = 0; i < grid->GetNumberCols() - 2; i++) {
        colSizeSum += grid->GetColSize(i);
    }
    // adjust message column width
    int newLastColSize = size.x - colSizeSum - 120;
    if (newLastColSize > 0)
        grid->SetColSize(grid->GetNumberCols() - 1, newLastColSize);
}

void MainGUIFrame::OnLogPanelSize(wxSizeEvent& event)
{
    // panel not floating (docked off)?
    if (!m_mgr.GetPane(pLog).IsFloating()) {
        expandGrid(logGrid, event.GetSize());
    }
}

void MainGUIFrame::OnDevicePanelSize(wxSizeEvent& event)
{
    // panel not floating (docked off)?
    if (!m_mgr.GetPane(pDevices).IsFloating()) {
        // adjust log grid size
        expandGrid(deviceGrid, event.GetSize());
    }
}

void MainGUIFrame::OnMenuSequenceNew(wxCommandEvent& event)
{
    controller->getContext()->logger->logDebug("OnMenuSequenceNew");
}

void MainGUIFrame::OnMenuDefaultChannelPreset(wxCommandEvent& event)
{
    controller->loadDefaultChannelSettings();
}

}; // namespace
