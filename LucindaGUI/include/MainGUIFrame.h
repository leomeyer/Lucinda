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
class ChannelPanel;

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
        wxVector<ChannelPanel*> channelPanels;

        void expandGrid(wxGrid* grid, const wxSize& size);

 		virtual void OnShow(wxShowEvent& event) override;
        virtual void OnClose(wxCloseEvent& event) override;
        virtual void OnQuit(wxCommandEvent& event) override;
        virtual void OnAbout(wxCommandEvent& event);

        void OnUpdateTimer(wxTimerEvent& event);

		virtual void OnChannelsSize( wxSizeEvent& event ) override;
        virtual void OnLogPanelSize(wxSizeEvent& event) override;
        virtual void OnDevicePanelSize(wxSizeEvent& event) override;
    };

}; // namespace

#endif // MAINGUIFRAME_H
