///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/grid.h>
#include <wx/aui/auibook.h>
#include <wx/frame.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/button.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxStatusBar* statusBar;
		wxMenuBar* mbMenuBar;
		wxMenu* m_menu3;
		wxMenu* m_menu4;
		wxMenu* m_menu5;
		wxMenu* m_menu41;
		wxAuiToolBar* m_auiToolBar1;
		wxAuiToolBarItem* tNew;
		wxAuiToolBarItem* mOpen;
		wxAuiToolBarItem* mSave;
		wxPanel* pSequenceProperties;
		wxPanel* m_panel85;
		wxStaticText* m_staticText13;
		wxTextCtrl* txtSequenceName;
		wxStaticText* m_staticText14;
		wxTextCtrl* txtSequenceDescription;
		wxPanel* m_panel89;
		wxStaticText* m_staticText15;
		wxStaticText* m_staticText16;
		wxPanel* pContent;
		wxBoxSizer* contentSizer;
		wxSplitterWindow* m_splitter1;
		wxScrolledWindow* pChannels;
		wxBoxSizer* channelSizer;
		wxPanel* m_panel54;
		wxStaticText* m_staticText17;
		wxPanel* pInformation;
		wxAuiNotebook* m_auinotebook4;
		wxPanel* pLog;
		wxGrid* logGrid;
		wxPanel* pDevices;
		wxGrid* deviceGrid;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnShow( wxShowEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChannelsSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnLogPanelSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnDevicePanelSize( wxSizeEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MainGUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 653,590 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~GUIFrame();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 0 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::m_splitter1OnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class SliderPanelBase
///////////////////////////////////////////////////////////////////////////////
class SliderPanelBase : public wxPanel
{
	private:

	protected:
		wxStaticText* stSliderName;
		wxStaticText* stLabel;
		wxTextCtrl* txtValue;
		wxPanel* m_panel78;
		wxStaticText* stMaxValue;
		wxSlider* slider;
		wxStaticText* stMinValue;

		// Virtual event handlers, overide them in your derived class
		virtual void OnValCharHook( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnFocusValue( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnValueEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnSlider( wxCommandEvent& event ) { event.Skip(); }


	public:

		SliderPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 60,-1 ), long style = wxBORDER_SIMPLE|wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~SliderPanelBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ChannelPanelBase
///////////////////////////////////////////////////////////////////////////////
class ChannelPanelBase : public wxPanel
{
	private:

	protected:
		wxBoxSizer* channelSizer;
		wxStaticText* stChannelName;
		wxPanel* pControls;
		wxPanel* pLights;
		wxPanel* m_panel53;
		wxPanel* m_panel54;
		wxCheckBox* cb1;
		wxPanel* m_panel55;
		wxPanel* m_panel56;
		wxPanel* m_panel57;
		wxPanel* m_panel58;
		wxCheckBox* cb5;
		wxPanel* m_panel60;
		wxPanel* m_panel61;
		wxCheckBox* cb2;
		wxCheckBox* cb6;
		wxCheckBox* cbHalogen;
		wxCheckBox* cb8;
		wxCheckBox* cb4;
		wxPanel* m_panel65;
		wxPanel* m_panel66;
		wxCheckBox* cb7;
		wxPanel* m_panel67;
		wxPanel* m_panel68;
		wxPanel* m_panel69;
		wxPanel* m_panel70;
		wxCheckBox* cb3;
		wxPanel* m_panel72;
		wxPanel* m_panel73;
		wxPanel* m_panel77;
		wxPanel* m_panel74;
		wxComboBox* cmbWaveform;
		wxCheckBox* cbReverse;
		wxCheckBox* cbInvert;
		wxCheckBox* cbEyeCorrection;
		wxPanel* m_panel79;
		wxStaticText* m_staticText10;
		wxTextCtrl* txtMCLength;
		wxStaticText* m_staticText11;
		wxTextCtrl* txtMCCount;
		wxStaticText* m_staticText12;
		wxTextCtrl* txtMCShift;
		wxPanel* m_panel80;
		wxCheckBox* cbEnabled;
		wxButton* btnSet;
		wxButton* btnReset;
		wxPanel* pInternal;
		wxBoxSizer* sizerInternal;

		// Virtual event handlers, overide them in your derived class
		virtual void OnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonSet( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonReset( wxCommandEvent& event ) { event.Skip(); }


	public:

		ChannelPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~ChannelPanelBase();

};

