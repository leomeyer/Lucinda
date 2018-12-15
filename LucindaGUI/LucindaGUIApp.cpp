/***************************************************************
 * Name:      LucindaGUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Leo Meyer (leo@leomeyer.de)
 * Created:   2018-12-14
 * Copyright: Leo Meyer ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <wx/persist/toplevel.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/msgdlg.h>

#include "LucindaGUIApp.h"
#include "LucindaGUIMain.h"

namespace APP_NAMESPACE {

IMPLEMENT_APP(LucindaGUIApp);

bool LucindaGUIApp::OnInit()
{
    wxApp::SetAppName(APP_INTERNAL_NAME);

    // store the local config files in the user's directory
    wxString userDir = wxStandardPaths::Get().GetUserDataDir();

    // make sure that data directory exists
    if (!wxDir::Make(userDir, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
        wxMessageDialog dlg(NULL, wxString("The directory for the configuration file could not be created: ") + userDir + "\nThe application will now exit.",
                            wxString(APP_NAME) + " Error", wxOK);
        dlg.ShowModal();
        return 1;
    }

    context.initialize(userDir + "/" + APP_CONFIG_LOCAL);

    wxString appTitle;
    context.config->getString("AppTitle", APP_NAME, &appTitle);

    LucindaGUIFrame* frame = new LucindaGUIFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->SetTitle(appTitle);

    if (!wxPersistentRegisterAndRestore(frame, "LucindaGUIFrame") )
    {
        // Choose some custom default size for the first run -- or don't do
        // anything at all and let the system use the default initial size.
        frame->SetClientSize(frame->FromDIP(wxSize(800, 600)));
    }

    frame->Show();

    return true;
}

}; // namespace
