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
    collectLevel = 0;
    isCollecting = false;
}

UndoManager::~UndoManager()
{
    //dtor
    // TODO
}

void UndoManager::addUndoChange(UndoChange* change)
{
    if (isCollecting) {
        // add the undo change to the list
        UndoChange* current = *(changes.end() - 1);
        current->changes.push_back(change);
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

        if (collectLevel > 0)
            isCollecting = true;
    }
}

void UndoManager::collect()
{
    collectLevel++;
}

void UndoManager::collectDone()
{
    if (collectLevel <= 0)
        throw std::runtime_error("Programming error: UndoManager::collectDone() called out of sequence");
    collectLevel--;
    if (collectLevel == 0) {
        controller->updateUndoState(this);
        isCollecting = false;
    }
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
        // collected change?
        if (change->changes.size() > 0) {
            // undo changes in reverse order
            auto end = changes.rend();
            for (auto iter = changes.rbegin(); iter != end; ++iter) {
                change->actor->undo(*iter);
            }
        }
        change->actor->undo(change);
        position--;
    }
}

void UndoManager::redo()
{
    if (position < changes.size()) {
        UndoChange* change = changes[position];
        change->actor->redo(change);
        // collected change?
        if (change->changes.size() > 0) {
            // redo changes in proper order
            auto end = changes.end();
            for (auto iter = changes.begin(); iter != end; ++iter) {
                change->actor->redo(*iter);
            }
        }
        position++;
    }
}

}; // namespace
