/***************************************************************
 * Name:      LucindaGUIApp.h
 * Purpose:   Defines Application Class
 * Author:    Leo Meyer (leo@leomeyer.de)
 * Created:   2018-12-14
 * Copyright: Leo Meyer ()
 * License:
 **************************************************************/

#ifndef LUCINDAGUIAPP_H
#define LUCINDAGUIAPP_H

#include <wx/app.h>

#include "LucindaGUIMain.h"

namespace APP_NAMESPACE {

class Context;
class ApplicationController;

class LucindaGUIApp : public wxApp
{
    public:
        virtual bool OnInit();

        Context* context;
        ApplicationController* appController;
};

}; // namespace

#endif // LUCINDAGUIAPP_H
