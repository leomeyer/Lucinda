#ifndef CHANNELCONTROLS_H
#define CHANNELCONTROLS_H

#include "GlobalDefines.h"

#include "../GUIFrame.h"

namespace APP_NAMESPACE {

class ChannelControls : public ChannelControlsBase
{
    public:
        ChannelControls(wxWindow* parent);
        virtual ~ChannelControls();

    protected:

    private:
};

};  // namespace

#endif // CHANNELCONTROLS_H
