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
#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/spinctrl.h>
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
		wxPanel* pLog;
		wxGrid* logGrid;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLogPanelSize( wxSizeEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MainGUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 653,590 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~GUIFrame();

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
		wxPanel* pInternal;
		wxBoxSizer* sizerInternal;

	public:

		ChannelPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 100,500 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~ChannelPanelBase();

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
		wxPanel* m_panel81;
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
/// Class ChannelControlsPanel
///////////////////////////////////////////////////////////////////////////////
class ChannelControlsPanel : public wxPanel
{
	private:

	protected:
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
		wxStaticText* m_staticText7;
		wxComboBox* m_comboBox1;
		wxCheckBox* m_checkBox82;
		wxPanel* m_panel78;
		wxCheckBox* m_checkBox83;
		wxCheckBox* m_checkBox84;
		wxPanel* m_panel79;
		wxStaticText* m_staticText10;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText11;
		wxSpinCtrl* m_spinCtrl2;
		wxStaticText* m_staticText12;
		wxSpinCtrl* m_spinCtrl3;
		wxPanel* m_panel80;
		wxCheckBox* m_checkBox85;
		wxButton* m_button1;

	public:

		ChannelControlsPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,100 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~ChannelControlsPanel();

};

