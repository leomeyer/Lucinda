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

#include "res/disk.png.h"
#include "res/folder.png.h"
#include "res/page_white_star.png.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	statusBar = this->CreateStatusBar( 2, wxSTB_SIZEGRIP, wxID_ANY );
	mbMenuBar = new wxMenuBar( 0 );
	m_menu3 = new wxMenu();
	wxMenuItem* miNew;
	miNew = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("New") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( miNew );

	wxMenuItem* miOpen;
	miOpen = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Open...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( miOpen );

	wxMenuItem* miSave;
	miSave = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( miSave );

	wxMenuItem* miSaveAs;
	miSaveAs = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( miSaveAs );

	m_menu3->AppendSeparator();

	wxMenuItem* miQuit;
	miQuit = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( miQuit );

	mbMenuBar->Append( m_menu3, wxT("Sequence") );

	m_menu4 = new wxMenu();
	mbMenuBar->Append( m_menu4, wxT("Edit") );

	m_menu5 = new wxMenu();
	mbMenuBar->Append( m_menu5, wxT("View") );

	this->SetMenuBar( mbMenuBar );

	m_auiToolBar1 = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	tNew = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), page_white_star_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	mOpen = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), folder_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	mSave = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), disk_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_auiToolBar1->AddSeparator();

	m_auiToolBar1->Realize();
	m_mgr.AddPane( m_auiToolBar1, wxAuiPaneInfo().Top().CaptionVisible( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 37,44 ) ).Row( 1 ) );

	pSequenceProperties = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,55 ), wxTAB_TRAVERSAL );
	pSequenceProperties->SetMinSize( wxSize( -1,40 ) );

	m_mgr.AddPane( pSequenceProperties, wxAuiPaneInfo() .Top() .CaptionVisible( false ).PinButton( true ).Movable( false ).Dock().Resizable().FloatingSize( wxSize( 37,54 ) ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).Row( 2 ) );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );

	m_panel85 = new wxPanel( pSequenceProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel85->SetMinSize( wxSize( -1,40 ) );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText13 = new wxStaticText( m_panel85, wxID_ANY, wxT("Sequence Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer34->Add( m_staticText13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	txtSequenceName = new wxTextCtrl( m_panel85, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( txtSequenceName, 0, wxALL, 1 );

	m_staticText14 = new wxStaticText( m_panel85, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer34->Add( m_staticText14, 0, wxALL, 5 );

	txtSequenceDescription = new wxTextCtrl( m_panel85, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( txtSequenceDescription, 9, wxALL, 1 );


	m_panel85->SetSizer( bSizer34 );
	m_panel85->Layout();
	bSizer34->Fit( m_panel85 );
	bSizer33->Add( m_panel85, 1, wxEXPAND | wxALL, 0 );

	m_panel89 = new wxPanel( pSequenceProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText15 = new wxStaticText( m_panel89, wxID_ANY, wxT("Length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer35->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	m_staticText16 = new wxStaticText( m_panel89, wxID_ANY, wxT("0 s"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer35->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_panel89->SetSizer( bSizer35 );
	m_panel89->Layout();
	bSizer35->Fit( m_panel89 );
	bSizer33->Add( m_panel89, 1, wxEXPAND | wxALL, 0 );


	pSequenceProperties->SetSizer( bSizer33 );
	pSequenceProperties->Layout();
	pContent = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( pContent, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxSize( 110,110 ) ).DockFixed( true ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );

	contentSizer = new wxBoxSizer( wxHORIZONTAL );


	pContent->SetSizer( contentSizer );
	pContent->Layout();
	contentSizer->Fit( pContent );
	pLog = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,80 ), wxTAB_TRAVERSAL );
	pLog->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	pLog->SetMinSize( wxSize( 100,80 ) );

	m_mgr.AddPane( pLog, wxAuiPaneInfo() .Bottom() .Caption( wxT("Log") ).PinButton( true ).Gripper().Dock().Resizable().FloatingSize( wxSize( 480,54 ) ).Layer( 1 ) );

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

	m_mgr.Update();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, miQuit->GetId());
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

	bSizer12->Add( stLabel, 0, wxALL, 1 );

	txtValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE );
	txtValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer12->Add( txtValue, 0, wxALL, 2 );


	bSizer11->Add( bSizer12, 1, 0, 5 );

	m_panel81 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer11->Add( m_panel81, 1, wxEXPAND | wxALL, 5 );

	stMaxValue = new wxStaticText( this, wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stMaxValue->Wrap( -1 );
	stMaxValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer11->Add( stMaxValue, 0, wxALL|wxEXPAND, 0 );

	slider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 30,330 ), wxSL_BOTH|wxSL_INVERSE|wxSL_VERTICAL );
	bSizer11->Add( slider, 0, wxALIGN_CENTER|wxALL, 1 );

	stMinValue = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stMinValue->Wrap( -1 );
	stMinValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer11->Add( stMinValue, 0, wxALL|wxEXPAND, 0 );


	this->SetSizer( bSizer11 );
	this->Layout();

	// Connect Events
	txtValue->Connect( wxEVT_CHAR_HOOK, wxKeyEventHandler( SliderPanelBase::OnValCharHook ), NULL, this );
	txtValue->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( SliderPanelBase::OnFocusValue ), NULL, this );
	txtValue->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SliderPanelBase::OnValueEnter ), NULL, this );
	slider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Connect( wxEVT_SLIDER, wxCommandEventHandler( SliderPanelBase::OnSlider ), NULL, this );
}

SliderPanelBase::~SliderPanelBase()
{
	// Disconnect Events
	txtValue->Disconnect( wxEVT_CHAR_HOOK, wxKeyEventHandler( SliderPanelBase::OnValCharHook ), NULL, this );
	txtValue->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( SliderPanelBase::OnFocusValue ), NULL, this );
	txtValue->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SliderPanelBase::OnValueEnter ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SliderPanelBase::OnSlider ), NULL, this );
	slider->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( SliderPanelBase::OnSlider ), NULL, this );

}

ChannelControlsPanel::ChannelControlsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	pLights = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED|wxTAB_TRAVERSAL );
	pLights->SetMinSize( wxSize( 80,75 ) );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 5, 5, 0, 0 );

	m_panel53 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel53, 1, wxEXPAND | wxALL, 5 );

	m_panel54 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel54, 1, wxEXPAND | wxALL, 5 );

	cb1 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb1, 0, wxALL, 2 );

	m_panel55 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel55, 1, wxEXPAND | wxALL, 5 );

	m_panel56 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel56, 1, wxEXPAND | wxALL, 5 );

	m_panel57 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel57, 1, wxEXPAND | wxALL, 5 );

	m_panel58 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel58, 1, wxEXPAND | wxALL, 5 );

	cb5 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb5, 0, wxALL, 2 );

	m_panel60 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel60, 1, wxEXPAND | wxALL, 5 );

	m_panel61 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel61, 1, wxEXPAND | wxALL, 5 );

	cb2 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb2, 0, wxALL, 2 );

	cb6 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb6, 0, wxALL, 2 );

	cbHalogen = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cbHalogen, 0, wxALL, 2 );

	cb8 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb8, 0, wxALL, 2 );

	cb4 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb4, 0, wxALL, 2 );

	m_panel65 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel65, 1, wxEXPAND | wxALL, 5 );

	m_panel66 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel66, 1, wxEXPAND | wxALL, 5 );

	cb7 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb7, 0, wxALL, 2 );

	m_panel67 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel67, 1, wxEXPAND | wxALL, 5 );

	m_panel68 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel68, 1, wxEXPAND | wxALL, 5 );

	m_panel69 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel69, 1, wxEXPAND | wxALL, 5 );

	m_panel70 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel70, 1, wxEXPAND | wxALL, 5 );

	cb3 = new wxCheckBox( pLights, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( cb3, 0, wxALL, 2 );

	m_panel72 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel72, 1, wxEXPAND | wxALL, 5 );

	m_panel73 = new wxPanel( pLights, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer3->Add( m_panel73, 1, wxEXPAND | wxALL, 5 );


	pLights->SetSizer( gSizer3 );
	pLights->Layout();
	gSizer3->Fit( pLights );
	fgSizer15->Add( pLights, 1, wxEXPAND | wxALL, 1 );

	m_panel77 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );

	m_panel74 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxSize( -1,30 ), wxTAB_TRAVERSAL );
	m_panel74->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_panel74->SetMaxSize( wxSize( -1,20 ) );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( m_panel74, wxID_ANY, wxT("Waveform"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer28->Add( m_staticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );

	m_comboBox1 = new wxComboBox( m_panel74, wxID_ANY, wxT("Square"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBox1->Append( wxT("Square") );
	m_comboBox1->Append( wxT("Sine") );
	m_comboBox1->Append( wxT("Triangle") );
	m_comboBox1->Append( wxT("Flicker") );
	m_comboBox1->Append( wxT("Linear") );
	bSizer28->Add( m_comboBox1, 0, wxALL, 0 );

	m_checkBox82 = new wxCheckBox( m_panel74, wxID_ANY, wxT("Rev"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_checkBox82, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	m_panel74->SetSizer( bSizer28 );
	m_panel74->Layout();
	bSizer29->Add( m_panel74, 1, wxALL, 0 );

	m_panel78 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );

	m_checkBox83 = new wxCheckBox( m_panel78, wxID_ANY, wxT("Invert"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox83->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer30->Add( m_checkBox83, 0, wxALL, 5 );

	m_checkBox84 = new wxCheckBox( m_panel78, wxID_ANY, wxT("Eye Correction"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox84->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer30->Add( m_checkBox84, 0, wxALL, 5 );


	m_panel78->SetSizer( bSizer30 );
	m_panel78->Layout();
	bSizer30->Fit( m_panel78 );
	bSizer29->Add( m_panel78, 1, wxEXPAND | wxALL, 0 );

	m_panel79 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText10 = new wxStaticText( m_panel79, wxID_ANY, wxT("ML"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_staticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_spinCtrl1 = new wxSpinCtrl( m_panel79, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	m_spinCtrl1->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_spinCtrl1->SetMaxSize( wxSize( 40,-1 ) );

	bSizer31->Add( m_spinCtrl1, 0, wxALL, 1 );

	m_staticText11 = new wxStaticText( m_panel79, wxID_ANY, wxT("MC"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_staticText11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0 );

	m_spinCtrl2 = new wxSpinCtrl( m_panel79, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	m_spinCtrl2->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_spinCtrl2->SetMaxSize( wxSize( 40,-1 ) );

	bSizer31->Add( m_spinCtrl2, 0, wxALL, 1 );

	m_staticText12 = new wxStaticText( m_panel79, wxID_ANY, wxT("MS"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	m_staticText12->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_staticText12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0 );

	m_spinCtrl3 = new wxSpinCtrl( m_panel79, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 40,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	m_spinCtrl3->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_spinCtrl3, 0, wxALL, 1 );


	m_panel79->SetSizer( bSizer31 );
	m_panel79->Layout();
	bSizer31->Fit( m_panel79 );
	bSizer29->Add( m_panel79, 1, wxEXPAND | wxALL, 0 );

	m_panel80 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );

	m_checkBox85 = new wxCheckBox( m_panel80, wxID_ANY, wxT("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBox85->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer32->Add( m_checkBox85, 0, wxALL, 5 );


	bSizer32->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button1 = new wxButton( m_panel80, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button1->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer32->Add( m_button1, 0, wxALL, 1 );


	m_panel80->SetSizer( bSizer32 );
	m_panel80->Layout();
	bSizer32->Fit( m_panel80 );
	bSizer29->Add( m_panel80, 1, wxEXPAND | wxALL, 0 );


	m_panel77->SetSizer( bSizer29 );
	m_panel77->Layout();
	bSizer29->Fit( m_panel77 );
	fgSizer15->Add( m_panel77, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( fgSizer15 );
	this->Layout();
}

ChannelControlsPanel::~ChannelControlsPanel()
{
}
