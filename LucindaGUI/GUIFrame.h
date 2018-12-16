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
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/slider.h>

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
		wxPanel* pLog;
		wxGrid* logGrid;
		wxPanel* pContent;
		wxFlexGridSizer* fgContentSizer;
		wxBoxSizer* bContentSizer;

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
		wxBoxSizer* bSizerInternal;
		wxStaticText* stChannelName;

	public:

		ChannelPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 80,501 ), long style = wxBORDER_SIMPLE|wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
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
		wxStaticText* m_staticText7;
		wxTextCtrl* txtValue;
		wxStaticText* stMaxValue;
		wxSlider* slider;
		wxStaticText* stMinValue;

		// Virtual event handlers, overide them in your derived class
		virtual void OnFocusValue( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnValueEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSlider( wxCommandEvent& event ) { event.Skip(); }


	public:

		SliderPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 80,450 ), long style = wxBORDER_SIMPLE|wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~SliderPanelBase();

};

