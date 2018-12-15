#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "../Arducom/src/master/ArducomMaster.h"

#include "Context.h"

namespace APP_NAMESPACE {

class Communication
{
    public:
        Communication(Context* context);
        virtual ~Communication();

    protected:
        Context* context;

    private:
};

}; // namespace

#endif // COMMUNICATION_H
