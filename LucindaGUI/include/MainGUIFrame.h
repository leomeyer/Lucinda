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

class Controller;
class ChannelPanel;
class UndoManager;

class MainGUIFrame: public GUIFrame
{
    public:
        MainGUIFrame(wxFrame *frame);
        ~MainGUIFrame();

        void initialize(Controller* controller);

        void applyGUISettings();

        void insertLogMessage(const Logger::LogMessage& message);

        void setStatusText(const wxString& statusText);

        void updateDeviceInfos(const wxVector<DeviceInfo>& deviceInfos);

        void updateUndoState(UndoManager* undoManager);

    private:
        Controller* controller;
        wxTimer* updateTimer;
        Logger::LogPriority minimumLogPriority;
        wxVector<ChannelPanel*> channelPanels;

        void expandGrid(wxGrid* grid, const wxSize& size);

        void OnUpdateTimer(wxTimerEvent& event);

   		virtual void OnUndo( wxCommandEvent& event ) override;
		virtual void OnRedo( wxCommandEvent& event ) override;

 		virtual void OnShow(wxShowEvent& event) override;
        virtual void OnClose(wxCloseEvent& event) override;
        virtual void OnQuit(wxCommandEvent& event) override;
        virtual void OnAbout(wxCommandEvent& event);

		virtual void OnSplitterChanging( wxSplitterEvent& event ) override;
		virtual void OnSplitterChanged( wxSplitterEvent& event ) override;

		virtual void OnChannelsSize( wxSizeEvent& event ) override;
        virtual void OnLogPanelSize(wxSizeEvent& event) override;
        virtual void OnDevicePanelSize(wxSizeEvent& event) override;

        virtual void OnMenuDefaultChannelPreset( wxCommandEvent& event ) override;

		virtual void OnMenuSequenceNew( wxCommandEvent& event ) override;

    };

}; // namespace

#endif // MAINGUIFRAME_H
