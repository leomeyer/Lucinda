#ifndef CONTEXT_H
#define CONTEXT_H

#include <wx/wx.h>

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

class Configuration;
class Logger;

class Context
{
    public:
        Context();
        virtual ~Context();

        Configuration* config;
        Logger* logger;

        void initialize(const wxString& configFileName);

    protected:

    private:
};

}; // namespace

#endif // CONTEXT_H
