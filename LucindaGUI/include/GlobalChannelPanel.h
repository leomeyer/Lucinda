#ifndef GLOBALCHANNELPANEL_H
#define GLOBALCHANNELPANEL_H

#include "GlobalDefines.h"

#include "../GUIFrame.h"
#include "ChannelPanel.h"

namespace APP_NAMESPACE {

class Processor;

class GlobalChannelPanel : public ChannelPanel
{
    public:
        GlobalChannelPanel(wxWindow* parent, Processor* processor);
        virtual ~GlobalChannelPanel();

    protected:

    private:
};

}; // namespace

#endif // GLOBALCHANNELPANEL_H
