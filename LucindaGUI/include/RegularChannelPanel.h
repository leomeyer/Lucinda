#ifndef REGULARCHANNELPANEL_H
#define REGULARCHANNELPANEL_H

#include <ChannelPanel.h>

namespace APP_NAMESPACE {

class RegularChannelPanel : public ChannelPanel
{
    public:
        RegularChannelPanel(wxWindow* parent, Controller* controller, uint8_t channel);
        virtual ~RegularChannelPanel();

    protected:

    private:
};

}; // namespace

#endif // REGULARCHANNELPANEL_H
