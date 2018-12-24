#include "UndoManager.h"
#include "Controller.h"

namespace APP_NAMESPACE {


UndoChange::UndoChange(IUndoRedoable* actor, int action, wxString label, void* data)
{
    this->actor = actor;
    this->action = action;
    this->label = label;
    this->data = data;
}

UndoChange::~UndoChange()
{
    if (data != nullptr)
        free(data);
}

UndoManager::UndoManager(Controller* controller)
{
    this->controller = controller;
    collecting = false;
}

UndoManager::~UndoManager()
{
    //dtor
}

void UndoManager::addUndoChange(UndoChange* change)
{
    if (collecting) {

    } else {
        if (changes.size() > position) {
            // delete objects to free memory
            auto end = changes.end();
            for (auto iter = changes.begin() + position; iter != end; ++iter)
                delete *iter;
            // clear changes list from position onwards
            changes.erase(changes.begin() + position, end);
        }
        changes.push_back(change);
        position = changes.size();
        controller->updateUndoState(this);
    }
}

void UndoManager::collect(UndoChange* change)
{

}

void UndoManager::collectDone()
{

}

bool UndoManager::canUndo()
{
    return position > 0;
}

bool UndoManager::canRedo()
{
    return position < changes.size();
}

wxString UndoManager::getUndoLabel()
{
    return changes.at(position - 1)->label;
}

wxString UndoManager::getRedoLabel()
{
    return changes.at(position)->label;
}

void UndoManager::undo()
{
    if (position > 0) {
        UndoChange* change = changes[position - 1];
        change->actor->undo(change);
        position--;
    }
}

void UndoManager::redo()
{
    if (position < changes.size()) {
        UndoChange* change = changes[position];
        change->actor->redo(change);
        position++;
    }
}


}; // namespace
