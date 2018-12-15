#ifndef ARDUCOMTHREAD_H
#define ARDUCOMTHREAD_H

#include <wx/thread.h>

namespace APP_NAMESPACE {


class ArducomThread : public wxThread
{
    public:
        ArducomThread();
        virtual ~ArducomThread();

    protected:

    private:
};

}; // namespace

#endif // ARDUCOMTHREAD_H
