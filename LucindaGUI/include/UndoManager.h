#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

struct UndoAction
{

};

class UndoManager
{
    public:
        UndoManager();
        virtual ~UndoManager();

        void addUndoAction(const UndoAction& action);

    protected:

    private:
};

}; // namespace

#endif // UNDOMANAGER_H
