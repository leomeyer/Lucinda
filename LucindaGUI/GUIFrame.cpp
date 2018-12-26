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

#include "res/arrow_redo.png.h"
#include "res/arrow_undo.png.h"
#include "res/control_end_blue.png.h"
#include "res/control_fastforward_blue.png.h"
#include "res/control_play_blue.png.h"
#include "res/control_repeat_blue.png.h"
#include "res/control_rewind_blue.png.h"
#include "res/control_start_blue.png.h"
#include "res/control_stop_blue.png.h"
#include "res/disk.png.h"
#include "res/folder.png.h"
#include "res/page_white_star.png.h"
#include "res/stop.png.h"
#include "res/table_delete.png.h"
#include "res/table_row_delete.png.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	statusBar = this->CreateStatusBar( 2, wxSTB_SIZEGRIP, wxID_ANY );
	mbMenuBar = new wxMenuBar( 0 );
	mnuSequence = new wxMenu();
	wxMenuItem* miNew;
	miNew = new wxMenuItem( mnuSequence, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	miNew->SetBitmaps( page_white_star_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	miNew->SetBitmap( page_white_star_png_to_wx_bitmap() );
	#endif
	mnuSequence->Append( miNew );

	wxMenuItem* miOpen;
	miOpen = new wxMenuItem( mnuSequence, wxID_ANY, wxString( wxT("Open...") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	miOpen->SetBitmaps( folder_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	miOpen->SetBitmap( folder_png_to_wx_bitmap() );
	#endif
	mnuSequence->Append( miOpen );

	wxMenuItem* miSave;
	miSave = new wxMenuItem( mnuSequence, wxID_ANY, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	miSave->SetBitmaps( disk_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	miSave->SetBitmap( disk_png_to_wx_bitmap() );
	#endif
	mnuSequence->Append( miSave );

	wxMenuItem* miSaveAs;
	miSaveAs = new wxMenuItem( mnuSequence, wxID_ANY, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSequence->Append( miSaveAs );

	mnuSequence->AppendSeparator();

	wxMenuItem* miQuit;
	miQuit = new wxMenuItem( mnuSequence, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	mnuSequence->Append( miQuit );

	mbMenuBar->Append( mnuSequence, wxT("Sequence") );

	mnuEdit = new wxMenu();
	miUndo = new wxMenuItem( mnuEdit, wxID_ANY, wxString( wxT("Undo") ) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	miUndo->SetBitmaps( arrow_undo_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	miUndo->SetBitmap( arrow_undo_png_to_wx_bitmap() );
	#endif
	mnuEdit->Append( miUndo );

	miRedo = new wxMenuItem( mnuEdit, wxID_ANY, wxString( wxT("Redo") ) + wxT('\t') + wxT("Ctrl+Y"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	miRedo->SetBitmaps( arrow_redo_png_to_wx_bitmap() );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	miRedo->SetBitmap( arrow_redo_png_to_wx_bitmap() );
	#endif
	mnuEdit->Append( miRedo );

	mbMenuBar->Append( mnuEdit, wxT("Edit") );

	mnuView = new wxMenu();
	mbMenuBar->Append( mnuView, wxT("View") );

	mnuDevices = new wxMenu();
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( mnuDevices, wxID_ANY, wxString( wxT("MyMenuItem") ) , wxEmptyString, wxITEM_NORMAL );
	mnuDevices->Append( m_menuItem6 );

	mbMenuBar->Append( mnuDevices, wxT("Devices") );

	mnuChannels = new wxMenu();
	m_menu1 = new wxMenu();
	wxMenuItem* m_menu1Item = new wxMenuItem( mnuChannels, wxID_ANY, wxT("Presets"), wxEmptyString, wxITEM_NORMAL, m_menu1 );
	wxMenuItem* miSetDefaultPreset;
	miSetDefaultPreset = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Set defaults") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( miSetDefaultPreset );

	mnuChannels->Append( m_menu1Item );

	mbMenuBar->Append( mnuChannels, wxT("Channels") );

	this->SetMenuBar( mbMenuBar );

	toolbar = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT );
	tNew = toolbar->AddTool( wxID_ANY, wxT("tool"), page_white_star_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("New"), wxEmptyString, NULL );

	tOpen = toolbar->AddTool( wxID_ANY, wxT("tool"), folder_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Open"), wxEmptyString, NULL );

	tSave = toolbar->AddTool( wxID_ANY, wxT("tool"), disk_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Save"), wxEmptyString, NULL );

	toolbar->AddSeparator();

	tUndo = toolbar->AddTool( wxID_ANY, wxT("tool"), arrow_undo_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Undo"), wxEmptyString, NULL );

	tRedo = toolbar->AddTool( wxID_ANY, wxT("tool"), arrow_redo_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Redo"), wxEmptyString, NULL );

	toolbar->Realize();
	m_mgr.AddPane( toolbar, wxAuiPaneInfo().Top().CaptionVisible( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 37,44 ) ).Row( 1 ) );

	pSequenceProperties = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,60 ), wxTAB_TRAVERSAL );
	pSequenceProperties->SetMinSize( wxSize( -1,60 ) );

	m_mgr.AddPane( pSequenceProperties, wxAuiPaneInfo() .Top() .CaptionVisible( false ).PinButton( true ).Movable( false ).Dock().Resizable().FloatingSize( wxSize( -1,-1 ) ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).Row( 2 ) );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );

	m_panel85 = new wxPanel( pSequenceProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel85->SetMinSize( wxSize( -1,40 ) );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText13 = new wxStaticText( m_panel85, wxID_ANY, wxT("Sequence Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer34->Add( m_staticText13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txtSequenceName = new wxTextCtrl( m_panel85, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( txtSequenceName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	m_staticText14 = new wxStaticText( m_panel85, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer34->Add( m_staticText14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	txtSequenceDescription = new wxTextCtrl( m_panel85, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( txtSequenceDescription, 9, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_panel85->SetSizer( bSizer34 );
	m_panel85->Layout();
	bSizer34->Fit( m_panel85 );
	bSizer33->Add( m_panel85, 1, wxALL|wxEXPAND, 0 );

	m_panel89 = new wxPanel( pSequenceProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText15 = new wxStaticText( m_panel89, wxID_ANY, wxT("Length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer35->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );

	m_staticText16 = new wxStaticText( m_panel89, wxID_ANY, wxT("0 s"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer35->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_panel89->SetSizer( bSizer35 );
	m_panel89->Layout();
	bSizer35->Fit( m_panel89 );
	bSizer33->Add( m_panel89, 1, wxALL|wxEXPAND, 0 );


	pSequenceProperties->SetSizer( bSizer33 );
	pSequenceProperties->Layout();
	pContent = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( pContent, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxSize( -1,-1 ) ).DockFixed( true ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );

	contentSizer = new wxBoxSizer( wxVERTICAL );

	contentSplitter = new wxSplitterWindow( pContent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME );
	contentSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::contentSplitterOnIdle ), NULL, this );

	pChannels = new wxScrolledWindow( contentSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	pChannels->SetScrollRate( 5, 5 );
	channelSizer = new wxBoxSizer( wxHORIZONTAL );


	pChannels->SetSizer( channelSizer );
	pChannels->Layout();
	channelSizer->Fit( pChannels );
	m_panel35 = new wxPanel( contentSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );

	m_notebook1 = new wxNotebook( m_panel35, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_notebook1->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	pTracks = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );

	trackSplitter = new wxSplitterWindow( pTracks, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_NO_XP_THEME );
	trackSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrame::trackSplitterOnIdle ), NULL, this );

	m_scrolledWindow2 = new wxScrolledWindow( trackSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	m_scrolledWindow3 = new wxScrolledWindow( trackSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow3->SetScrollRate( 5, 5 );
	trackSplitter->SplitVertically( m_scrolledWindow2, m_scrolledWindow3, 100 );
	bSizer25->Add( trackSplitter, 1, wxEXPAND, 5 );


	pTracks->SetSizer( bSizer25 );
	pTracks->Layout();
	bSizer25->Fit( pTracks );
	m_notebook1->AddPage( pTracks, wxT("Tracks"), false );
	pEvents = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pEvents->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	m_toolBar2 = new wxToolBar( pEvents, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	tbClearEvents = m_toolBar2->AddTool( wxID_ANY, wxT("tool"), table_delete_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Clear all events"), wxEmptyString, NULL );

	tbDeleteEvents = m_toolBar2->AddTool( wxID_ANY, wxT("tool"), table_row_delete_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Delete selected events"), wxEmptyString, NULL );

	m_toolBar2->Realize();

	bSizer21->Add( m_toolBar2, 0, wxEXPAND, 5 );

	eventGrid = new wxGrid( pEvents, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	eventGrid->CreateGrid( 0, 3 );
	eventGrid->EnableEditing( false );
	eventGrid->EnableGridLines( true );
	eventGrid->EnableDragGridSize( false );
	eventGrid->SetMargins( 0, 0 );

	// Columns
	eventGrid->SetColSize( 0, 80 );
	eventGrid->SetColSize( 1, 107 );
	eventGrid->SetColSize( 2, 402 );
	eventGrid->EnableDragColMove( false );
	eventGrid->EnableDragColSize( true );
	eventGrid->SetColLabelSize( 20 );
	eventGrid->SetColLabelValue( 0, wxT("Time") );
	eventGrid->SetColLabelValue( 1, wxT("Event") );
	eventGrid->SetColLabelValue( 2, wxT("Data") );
	eventGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	eventGrid->EnableDragRowSize( true );
	eventGrid->SetRowLabelSize( 0 );
	eventGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	eventGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer21->Add( eventGrid, 1, wxALL|wxEXPAND, 5 );


	pEvents->SetSizer( bSizer21 );
	pEvents->Layout();
	bSizer21->Fit( pEvents );
	m_notebook1->AddPage( pEvents, wxT("Events"), true );

	bSizer22->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );


	m_panel35->SetSizer( bSizer22 );
	m_panel35->Layout();
	bSizer22->Fit( m_panel35 );
	contentSplitter->SplitHorizontally( pChannels, m_panel35, 0 );
	contentSizer->Add( contentSplitter, 1, wxEXPAND, 5 );

	m_toolBar1 = new wxToolBar( pContent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	tbRecord = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), stop_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbStop = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_stop_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbPlay = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_play_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbStart = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_start_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbBack = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_rewind_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbForward = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_fastforward_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbEnd = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_end_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	tbRepeat = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), control_repeat_blue_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();

	contentSizer->Add( m_toolBar1, 0, wxEXPAND, 5 );


	pContent->SetSizer( contentSizer );
	pContent->Layout();
	contentSizer->Fit( pContent );
	pInformation = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,100 ), wxTAB_TRAVERSAL );
	pInformation->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	pInformation->SetMinSize( wxSize( 100,80 ) );

	m_mgr.AddPane( pInformation, wxAuiPaneInfo() .Bottom() .Caption( wxT("Log") ).CaptionVisible( false ).PinButton( true ).Gripper().Dock().Resizable().FloatingSize( wxSize( 480,54 ) ).Row( 0 ).Layer( 1 ) );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	m_auinotebook4 = new wxAuiNotebook( pInformation, wxID_ANY, wxDefaultPosition, wxSize( -1,80 ), wxAUI_NB_DEFAULT_STYLE );
	m_auinotebook4->SetMinSize( wxSize( -1,80 ) );

	pLog = new wxPanel( m_auinotebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	fgSizer2->Fit( pLog );
	m_auinotebook4->AddPage( pLog, wxT("Log"), true, wxNullBitmap );
	pDevices = new wxPanel( m_auinotebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );

	deviceGrid = new wxGrid( pDevices, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	deviceGrid->CreateGrid( 1, 7 );
	deviceGrid->EnableEditing( false );
	deviceGrid->EnableGridLines( true );
	deviceGrid->EnableDragGridSize( false );
	deviceGrid->SetMargins( 0, 0 );

	// Columns
	deviceGrid->SetColSize( 0, 64 );
	deviceGrid->SetColSize( 1, 89 );
	deviceGrid->SetColSize( 2, 80 );
	deviceGrid->SetColSize( 3, 59 );
	deviceGrid->SetColSize( 4, 64 );
	deviceGrid->SetColSize( 5, 89 );
	deviceGrid->SetColSize( 6, 165 );
	deviceGrid->EnableDragColMove( false );
	deviceGrid->EnableDragColSize( true );
	deviceGrid->SetColLabelSize( 30 );
	deviceGrid->SetColLabelValue( 0, wxT("Address") );
	deviceGrid->SetColLabelValue( 1, wxT("Status") );
	deviceGrid->SetColLabelValue( 2, wxT("Name") );
	deviceGrid->SetColLabelValue( 3, wxT("Free RAM") );
	deviceGrid->SetColLabelValue( 4, wxT("Uptime") );
	deviceGrid->SetColLabelValue( 5, wxT("Parameters") );
	deviceGrid->SetColLabelValue( 6, wxT("Info") );
	deviceGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	deviceGrid->EnableDragRowSize( true );
	deviceGrid->SetRowLabelSize( 0 );
	deviceGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	deviceGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer16->Add( deviceGrid, 0, wxALL|wxEXPAND, 1 );


	pDevices->SetSizer( bSizer16 );
	pDevices->Layout();
	bSizer16->Fit( pDevices );
	m_auinotebook4->AddPage( pDevices, wxT("Devices"), false, wxNullBitmap );

	bSizer15->Add( m_auinotebook4, 1, wxEXPAND | wxALL, 0 );


	pInformation->SetSizer( bSizer15 );
	pInformation->Layout();

	m_mgr.Update();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( wxEVT_SHOW, wxShowEventHandler( GUIFrame::OnShow ) );
	mnuSequence->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuSequenceNew ), this, miNew->GetId());
	mnuSequence->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, miQuit->GetId());
	mnuEdit->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnUndo ), this, miUndo->GetId());
	mnuEdit->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRedo ), this, miRedo->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuDefaultChannelPreset ), this, miSetDefaultPreset->GetId());
	this->Connect( tUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnUndo ));
	this->Connect( tRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRedo ));
	contentSplitter->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( GUIFrame::OnSplitterChanged ), NULL, this );
	contentSplitter->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, wxSplitterEventHandler( GUIFrame::OnSplitterChanging ), NULL, this );
	pChannels->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnChannelsSize ), NULL, this );
	pLog->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnLogPanelSize ), NULL, this );
	pDevices->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnDevicePanelSize ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxEVT_SHOW, wxShowEventHandler( GUIFrame::OnShow ) );
	this->Disconnect( tUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnUndo ));
	this->Disconnect( tRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRedo ));
	contentSplitter->Disconnect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( GUIFrame::OnSplitterChanged ), NULL, this );
	contentSplitter->Disconnect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING, wxSplitterEventHandler( GUIFrame::OnSplitterChanging ), NULL, this );
	pChannels->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnChannelsSize ), NULL, this );
	pLog->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnLogPanelSize ), NULL, this );
	pDevices->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnDevicePanelSize ), NULL, this );

	m_mgr.UnInit();

}

SliderPanelBase::SliderPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetMinSize( wxSize( 60,-1 ) );

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


	bSizer11->Add( bSizer12, 0, 0, 5 );

	m_panel78 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );

	stMaxValue = new wxStaticText( m_panel78, wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stMaxValue->Wrap( -1 );
	stMaxValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer33->Add( stMaxValue, 0, wxALL|wxEXPAND, 0 );

	slider = new wxSlider( m_panel78, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( -1,-1 ), wxSL_BOTH|wxSL_INVERSE|wxSL_VERTICAL );
	bSizer33->Add( slider, 1, wxALIGN_CENTER|wxALL, 1 );

	stMinValue = new wxStaticText( m_panel78, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	stMinValue->Wrap( -1 );
	stMinValue->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer33->Add( stMinValue, 0, wxALL|wxEXPAND, 0 );


	m_panel78->SetSizer( bSizer33 );
	m_panel78->Layout();
	bSizer33->Fit( m_panel78 );
	bSizer11->Add( m_panel78, 1, wxEXPAND | wxALL, 5 );


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
	slider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SliderPanelBase::OnSliderRelease ), NULL, this );
	slider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SliderPanelBase::OnSliderTrack ), NULL, this );
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
	slider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SliderPanelBase::OnSliderRelease ), NULL, this );
	slider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SliderPanelBase::OnSliderTrack ), NULL, this );
	slider->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( SliderPanelBase::OnSlider ), NULL, this );

}

ChannelPanelBase::ChannelPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );

	channelSizer = new wxBoxSizer( wxVERTICAL );

	stChannelName = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	stChannelName->Wrap( -1 );
	stChannelName->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	channelSizer->Add( stChannelName, 0, wxALL|wxEXPAND, 2 );

	pGlobalControls = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	btnSendAll = new wxButton( pGlobalControls, wxID_ANY, wxT("Send All"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSendAll->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer21->Add( btnSendAll, 0, wxALL, 0 );

	btnSyncAll = new wxButton( pGlobalControls, wxID_ANY, wxT("Synchronize"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSyncAll->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer21->Add( btnSyncAll, 0, wxALL, 0 );


	pGlobalControls->SetSizer( bSizer21 );
	pGlobalControls->Layout();
	bSizer21->Fit( pGlobalControls );
	channelSizer->Add( pGlobalControls, 0, wxALL|wxFIXED_MINSIZE, 1 );

	pControls = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxHORIZONTAL );

	pLights = new wxPanel( pControls, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxBORDER_RAISED|wxTAB_TRAVERSAL );
	pLights->SetMaxSize( wxSize( 100,100 ) );

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
	bSizer32->Add( pLights, 1, wxALL|wxEXPAND, 1 );

	m_panel77 = new wxPanel( pControls, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );

	m_panel74 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	m_panel74->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	cmbWaveform = new wxComboBox( m_panel74, wxID_ANY, wxT("Square"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	cmbWaveform->Append( wxT("Square") );
	cmbWaveform->Append( wxT("Sine") );
	cmbWaveform->Append( wxT("Triangle") );
	cmbWaveform->Append( wxT("Flicker") );
	cmbWaveform->Append( wxT("Linear") );
	cmbWaveform->SetMaxSize( wxSize( -1,16 ) );

	bSizer28->Add( cmbWaveform, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 0 );

	cbReverse = new wxCheckBox( m_panel74, wxID_ANY, wxT("Rev"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( cbReverse, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );

	cbInvert = new wxCheckBox( m_panel74, wxID_ANY, wxT("Inv"), wxDefaultPosition, wxDefaultSize, 0 );
	cbInvert->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer28->Add( cbInvert, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );

	cbEyeCorrection = new wxCheckBox( m_panel74, wxID_ANY, wxT("Eye"), wxDefaultPosition, wxDefaultSize, 0 );
	cbEyeCorrection->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer28->Add( cbEyeCorrection, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );


	m_panel74->SetSizer( bSizer28 );
	m_panel74->Layout();
	bSizer28->Fit( m_panel74 );
	bSizer29->Add( m_panel74, 0, wxTOP|wxBOTTOM, 3 );

	m_panel79 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText10 = new wxStaticText( m_panel79, wxID_ANY, wxT("MC Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_staticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtMCLength = new wxTextCtrl( m_panel79, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	txtMCLength->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	txtMCLength->SetMaxSize( wxSize( 30,18 ) );

	bSizer31->Add( txtMCLength, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	m_staticText11 = new wxStaticText( m_panel79, wxID_ANY, wxT("Count"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_staticText11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtMCCount = new wxTextCtrl( m_panel79, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	txtMCCount->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	txtMCCount->SetMaxSize( wxSize( 30,18 ) );

	bSizer31->Add( txtMCCount, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );

	m_staticText12 = new wxStaticText( m_panel79, wxID_ANY, wxT("Shift"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	m_staticText12->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer31->Add( m_staticText12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtMCShift = new wxTextCtrl( m_panel79, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	txtMCShift->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	txtMCShift->SetMaxSize( wxSize( 30,18 ) );

	bSizer31->Add( txtMCShift, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1 );


	m_panel79->SetSizer( bSizer31 );
	m_panel79->Layout();
	bSizer31->Fit( m_panel79 );
	bSizer29->Add( m_panel79, 0, wxTOP|wxBOTTOM, 3 );

	m_panel80 = new wxPanel( m_panel77, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer321;
	bSizer321 = new wxBoxSizer( wxHORIZONTAL );

	cbEnabled = new wxCheckBox( m_panel80, wxID_ANY, wxT("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	cbEnabled->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer321->Add( cbEnabled, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxFIXED_MINSIZE, 1 );

	btnSend = new wxButton( m_panel80, wxID_ANY, wxT("Send"), wxDefaultPosition, wxSize( 30,-1 ), 0 );
	btnSend->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer321->Add( btnSend, 1, wxALL, 1 );

	btnReset = new wxButton( m_panel80, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	btnReset->SetFont( wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer321->Add( btnReset, 1, wxALL, 1 );


	m_panel80->SetSizer( bSizer321 );
	m_panel80->Layout();
	bSizer321->Fit( m_panel80 );
	bSizer29->Add( m_panel80, 0, wxTOP|wxBOTTOM, 3 );


	m_panel77->SetSizer( bSizer29 );
	m_panel77->Layout();
	bSizer29->Fit( m_panel77 );
	bSizer32->Add( m_panel77, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	pControls->SetSizer( bSizer32 );
	pControls->Layout();
	bSizer32->Fit( pControls );
	channelSizer->Add( pControls, 0, wxALL, 2 );

	pInternal = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	sizerInternal = new wxBoxSizer( wxHORIZONTAL );


	pInternal->SetSizer( sizerInternal );
	pInternal->Layout();
	sizerInternal->Fit( pInternal );
	channelSizer->Add( pInternal, 10, wxALL|wxEXPAND, 5 );


	this->SetSizer( channelSizer );
	this->Layout();

	// Connect Events
	btnSendAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnSendAll ), NULL, this );
	btnSyncAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnSynchronize ), NULL, this );
	cb1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb5->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb6->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cbHalogen->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb8->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb4->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb7->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb3->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cmbWaveform->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ChannelPanelBase::OnCombobox ), NULL, this );
	cbReverse->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cbInvert->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cbEyeCorrection->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	txtMCLength->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ChannelPanelBase::OnTextKillFocus ), NULL, this );
	txtMCLength->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ChannelPanelBase::OnText ), NULL, this );
	txtMCLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ChannelPanelBase::OnTextEnter ), NULL, this );
	txtMCCount->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ChannelPanelBase::OnTextKillFocus ), NULL, this );
	txtMCCount->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ChannelPanelBase::OnText ), NULL, this );
	txtMCCount->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ChannelPanelBase::OnTextEnter ), NULL, this );
	txtMCShift->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ChannelPanelBase::OnTextKillFocus ), NULL, this );
	txtMCShift->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ChannelPanelBase::OnText ), NULL, this );
	txtMCShift->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ChannelPanelBase::OnTextEnter ), NULL, this );
	cbEnabled->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	btnSend->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnButtonSend ), NULL, this );
	btnReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnButtonReset ), NULL, this );
}

ChannelPanelBase::~ChannelPanelBase()
{
	// Disconnect Events
	btnSendAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnSendAll ), NULL, this );
	btnSyncAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnSynchronize ), NULL, this );
	cb1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb5->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb6->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cbHalogen->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb8->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb4->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb7->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cb3->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cmbWaveform->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ChannelPanelBase::OnCombobox ), NULL, this );
	cbReverse->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cbInvert->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	cbEyeCorrection->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	txtMCLength->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ChannelPanelBase::OnTextKillFocus ), NULL, this );
	txtMCLength->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ChannelPanelBase::OnText ), NULL, this );
	txtMCLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ChannelPanelBase::OnTextEnter ), NULL, this );
	txtMCCount->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ChannelPanelBase::OnTextKillFocus ), NULL, this );
	txtMCCount->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ChannelPanelBase::OnText ), NULL, this );
	txtMCCount->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ChannelPanelBase::OnTextEnter ), NULL, this );
	txtMCShift->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( ChannelPanelBase::OnTextKillFocus ), NULL, this );
	txtMCShift->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( ChannelPanelBase::OnText ), NULL, this );
	txtMCShift->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( ChannelPanelBase::OnTextEnter ), NULL, this );
	cbEnabled->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnCheckBox ), NULL, this );
	btnSend->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnButtonSend ), NULL, this );
	btnReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ChannelPanelBase::OnButtonReset ), NULL, this );

}

GlobalControlsPanel::GlobalControlsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
}

GlobalControlsPanel::~GlobalControlsPanel()
{
}
