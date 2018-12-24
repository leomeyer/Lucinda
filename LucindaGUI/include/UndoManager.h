#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <memory>
#include <wx/wx.h>

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

class UndoChange
{
    public:
        IUndoRedoable* actor;    // the object responsible for undoing/redoing the change
        int action;             // what has been changed (specific to the actor)
        wxString label;         // what to show to the user
        void* data;             // pointer to previous state

        // create an UndoChange
        UndoChange(IUndoRedoable* actor, int action, wxString label, void* data = nullptr);

        // when this object is destroyed associated data is automatically freed
        virtual ~UndoChange();

    protected:
        std::vector<UndoChange*> changes;   // list of cumulated changes

friend class UndoManager;
};

class Controller;

class UndoManager
{
    public:
        UndoManager(Controller* controller);
        virtual ~UndoManager();

        // this object becomes owner of the data in change
        // and will free it on its own
        void addUndoChange(UndoChange* change);

        // if multiple changes are to be collected, start by calling this method
        void collect(UndoChange* change);

        // must be called when all changes to collect have been made
        void collectDone();

        // returns true if there is something to undo
        bool canUndo();

        // returns true if there is something to redo
        bool canRedo();

        wxString getUndoLabel();

        wxString getRedoLabel();

        // perform an undo
        void undo();

        // perform a redo
        void redo();

    protected:
        Controller* controller;
        bool collecting;

        std::vector<UndoChange*> changes;
        // current undo position, will be 0 if the list is empty
        // otherwise, is the index plus one of the element to undo
        size_t position;

    private:
};

}; // namespace

#endif // UNDOMANAGER_H
