// https://usingcpp.wordpress.com/2016/01/26/creating-wxwidgets-programs-with-visual-studio-2015/

#include <wx/wxprec.h>
#include "LucindaGUI.h"
#include "MainFrame.h"

#ifdef _UNICODE
#ifdef _DEBUG
#pragma comment(lib, "wxbase31ud.lib")
#else
#pragma comment(lib, "wxbase31u.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "wxbase31d.lib")
#else
#pragma comment(lib, "wxbase31.lib")
#endif
#endif

LucindaGUI::LucindaGUI()
{
}

LucindaGUI::~LucindaGUI()
{
}

bool LucindaGUI::OnInit()
{
	wxPuts(wxT("A wxWidgets console application"));

	// wxFrame* mainFrame = new wxFrame(nullptr, wxID_ANY, L"LucindaGUI");
	// mainFrame->Show(true);

	MainFrame* mainFrame = new MainFrame(L"LucindaGUI");
	mainFrame->Show(true);

	return true;
}

wxIMPLEMENT_APP(LucindaGUI);