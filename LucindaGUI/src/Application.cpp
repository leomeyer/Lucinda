/***************************************************************
 * Name:      Application.cpp
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

#include "Configuration.h"
#include "Context.h"
#include "Communication.h"
#include "Controller.h"

#include "Application.h"


namespace APP_NAMESPACE {

IMPLEMENT_APP(Application);

bool Application::OnInit()
{
    wxApp::SetAppName(APP_INTERNAL_NAME);

    wxInitAllImageHandlers();

    // store the local config files in the user's directory
    wxString userDir = wxStandardPaths::Get().GetUserDataDir();

    // make sure that data directory exists
    if (!wxDir::Make(userDir, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
        wxMessageDialog dlg(NULL, wxString("The directory for the configuration file could not be created: ") + userDir + "\nThe application will now exit.",
                            wxString(APP_NAME) + " Error", wxOK);
        dlg.ShowModal();
        return 1;
    }

    context = new Context();
    context->initialize(userDir + "/" + APP_CONFIG_LOCAL);

    wxString appTitle;
    context->config->getString("AppTitle", APP_NAME, &appTitle);

    // create main frame
    MainGUIFrame* frame = new MainGUIFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->SetTitle(appTitle);

    if (!wxPersistentRegisterAndRestore(frame, "MainGUIFrame") )
    {
        // Choose some custom default size for the first run -- or don't do
        // anything at all and let the system use the default initial size.
        frame->SetClientSize(frame->FromDIP(wxSize(800, 600)));
    }

    // initialize application controller
    controller = new Controller(context, new Communication(context), frame);
    controller->start();
    frame->initialize(controller);

        frame->Show();

    frame->applyGUISettings();

    return true;
}

}; // namespace
