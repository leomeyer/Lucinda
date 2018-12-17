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
	mbMenuBar = new wxMenuBar( 0 );
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem3 );

	mbMenuBar->Append( m_menu3, wxT("MyMenu") );

	this->SetMenuBar( mbMenuBar );

	pLog = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,80 ), wxTAB_TRAVERSAL );
	pLog->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	pLog->SetMinSize( wxSize( 100,80 ) );

	m_mgr.AddPane( pLog, wxAuiPaneInfo() .Bottom() .Caption( wxT("Log") ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 480,54 ) ).Layer( 1 ) );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 1, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	logGrid = new wxGrid( pLog, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	logGrid->CreateGrid( 0, 3 );
	logGrid->EnableEditing( false );
	logGrid->EnableGridLines( true );
	logGrid->EnableDragGridSize( false );
	logGrid->SetMargins( 0, 0 );

	// Columns
	logGrid->SetColSize( 0, 70 );
	logGrid->SetColSize( 1, 60 );
	logGrid->SetColSize( 2, 500 );
	logGrid->EnableDragColMove( false );
	logGrid->EnableDragColSize( true );
	logGrid->SetColLabelSize( 20 );
	logGrid->SetColLabelValue( 0, wxT("Time") );
	logGrid->SetColLabelValue( 1, wxT("Priority") );
	logGrid->SetColLabelValue( 2, wxT("Message") );
	logGrid->SetColLabelAlignment( wxALIGN_LEFT, wxALIGN_CENTER );

	// Rows
	logGrid->EnableDragRowSize( true );
	logGrid->SetRowLabelSize( 0 );
	logGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	logGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer7->Add( logGrid, 1, wxEXPAND, 1 );


	fgSizer2->Add( bSizer7, 1, wxEXPAND, 5 );


	pLog->SetSizer( fgSizer2 );
	pLog->Layout();
	pContent = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( pContent, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxSize( 110,110 ) ).DockFixed( true ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );

	contentSizer = new wxBoxSizer( wxHORIZONTAL );


	pContent->SetSizer( contentSizer );
	pContent->Layout();
	contentSizer->Fit( pContent );

	m_mgr.Update();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, m_menuItem3->GetId());
	pLog->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnLogPanelSize ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	pLog->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnLogPanelSize ), NULL, this );

	m_mgr.UnInit();

}

ChannelPanelBase::ChannelPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNSHADOW ) );
	this->SetMinSize( wxSize( 0,500 ) );

	channelSizer = new wxBoxSizer( wxVERTICAL );

	stChannelName = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	stChannelName->Wrap( -1 );
	channelSizer->Add( stChannelName, 0, wxALL|wxEXPAND, 5 );

	pInternal = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerInternal = new wxBoxSizer( wxHORIZONTAL );


	pInternal->SetSizer( sizerInternal );
	pInternal->Layout();
	sizerInternal->Fit( pInternal );
	channelSizer->Add( pInternal, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( channelSizer );
	this->Layout();
}

ChannelPanelBase::~ChannelPanelBase()
{
}

SliderPanelBase::SliderPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetMinSize( wxSize( 60,450 ) );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	stSliderName = new wxStaticText( this, wxID_ANY, wxT("SliderName"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stSliderName->Wrap( -1 );
	stSliderName->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer11->Add( stSliderName, 0, wxALL|wxEXPAND, 2 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	stLabel = new wxStaticText( this, wxID_ANY, wxT("Val"), wxDefaultPosition, wxDefaultSize, 0 );
	stLabel->Wrap( -1 );
	stLabel->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer12->Add( stLabel, 0, wxALL, 5 );

	txtValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	txtValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer12->Add( txtValue, 0, wxALL, 2 );


	bSizer11->Add( bSizer12, 1, 0, 5 );

	stMaxValue = new wxStaticText( this, wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stMaxValue->Wrap( -1 );
	stMaxValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer11->Add( stMaxValue, 0, wxALL|wxEXPAND, 0 );

	slider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 30,330 ), wxSL_BOTH|wxSL_INVERSE|wxSL_SELRANGE|wxSL_VERTICAL );
	bSizer11->Add( slider, 0, wxALIGN_CENTER|wxALL, 1 );

	stMinValue = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stMinValue->Wrap( -1 );
	stMinValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer11->Add( stMinValue, 0, wxALL|wxEXPAND, 0 );


	this->SetSizer( bSizer11 );
	this->Layout();

	// Connect Events
	txtValue->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( SliderPanelBase::OnFocusValue ), NULL, this );
	txtValue->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SliderPanelBase::OnValueEnter ), NULL, this );
	slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( SliderPanelBase::OnSlider ), NULL, this );
}

SliderPanelBase::~SliderPanelBase()
{
	// Disconnect Events
	txtValue->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( SliderPanelBase::OnFocusValue ), NULL, this );
	txtValue->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SliderPanelBase::OnValueEnter ), NULL, this );
	slider->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( SliderPanelBase::OnSlider ), NULL, this );

}
