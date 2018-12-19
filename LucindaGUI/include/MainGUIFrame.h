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
#include "../GUIFrame.h"
#include "DeviceInfo.h"

#include "Logger.h"

namespace APP_NAMESPACE {

class ApplicationController;

class MainGUIFrame: public GUIFrame
{
    public:
        MainGUIFrame(wxFrame *frame);
        ~MainGUIFrame();

        void initialize(ApplicationController* appController);

        void insertLogMessage(const Logger::LogMessage& message);

        void setStatusText(const wxString& statusText);

        void updateDeviceInfos(const wxVector<DeviceInfo>& deviceInfos);

    private:
        ApplicationController* appController;
        wxTimer* updateTimer;
        Logger::LogPriority minimumLogPriority;

 		virtual void OnShow(wxShowEvent& event);
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);

        void OnUpdateTimer(wxTimerEvent& event);

        virtual void OnLogPanelSize(wxSizeEvent& event) override;
        virtual void OnDevicePanelSize(wxSizeEvent& event) override;
    };

}; // namespace

#endif // MAINGUIFRAME_H
