/***************************************************************
 * Name:      Application.h
 * Purpose:   Defines Application Class
 * Author:    Leo Meyer (leo@leomeyer.de)
 * Created:   2018-12-14
 * Copyright: Leo Meyer ()
 * License:
 **************************************************************/

#ifndef APPPLICATION_H
#define APPPLICATION_H

#include <wx/app.h>

#include "MainGUIFrame.h"

namespace APP_NAMESPACE {

class Context;
class Controller;

class Application : public wxApp
{
    public:
        virtual bool OnInit();

        Context* context;
        Controller* controller;
};

}; // namespace

#endif // APPPLICATION_H
