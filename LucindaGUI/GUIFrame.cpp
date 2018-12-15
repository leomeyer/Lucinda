///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	statusBar = this->CreateStatusBar( 2, wxSTB_SIZEGRIP, wxID_ANY );
	m_menubar2 = new wxMenuBar( 0 );
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem3 );

	m_menubar2->Append( m_menu3, wxT("MyMenu") );

	this->SetMenuBar( m_menubar2 );


	m_mgr.Update();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, m_menuItem3->GetId());
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );

	m_mgr.UnInit();

}

LogPanel::LogPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	logGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	logGrid->CreateGrid( 0, 2 );
	logGrid->EnableEditing( true );
	logGrid->EnableGridLines( true );
	logGrid->EnableDragGridSize( false );
	logGrid->SetMargins( 0, 0 );

	// Columns
	logGrid->SetColSize( 0, 80 );
	logGrid->SetColSize( 1, 500 );
	logGrid->EnableDragColMove( false );
	logGrid->EnableDragColSize( true );
	logGrid->SetColLabelSize( 20 );
	logGrid->SetColLabelValue( 0, wxT("Time") );
	logGrid->SetColLabelValue( 1, wxT("Message") );
	logGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	logGrid->EnableDragRowSize( true );
	logGrid->SetRowLabelSize( 0 );
	logGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	logGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer1->Add( logGrid, 1, wxALIGN_LEFT|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
}

LogPanel::~LogPanel()
{
}
