#ifndef CONTEXT_H
#define CONTEXT_H

#include <wx/wx.h>

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

class Configuration;
class Logger;
class Processor;
class ColorManagement;
class UndoManager;

class Context
{
    public:
        Context();
        virtual ~Context();

        Configuration* config;
        Logger* logger;
        Processor* processor;
        ColorManagement* colorManagement;
        UndoManager* undoManager;

        void initialize(const wxString& configFileName);

    protected:

    private:
};

}; // namespace

#endif // CONTEXT_H
