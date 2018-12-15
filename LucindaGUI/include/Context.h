#ifndef CONTEXT_H
#define CONTEXT_H

#include "GlobalDefines.h"
#include "Configuration.h"

namespace APP_NAMESPACE {

class Context
{
    public:
        Context();
        virtual ~Context();

        Configuration* config;

        void initialize(const wxString& configFileName);

    protected:

    private:
};

}; // namespace

#endif // CONTEXT_H
