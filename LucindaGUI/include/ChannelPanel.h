#ifndef CHANNELPANEL_H
#define CHANNELPANEL_H

#include "GlobalDefines.h"

#include "../GUIFrame.h"

namespace APP_NAMESPACE {

class Processor;

class ChannelPanel : public ChannelPanelBase
{
    public:
        ChannelPanel(wxWindow* parent, Processor* processor, const wxString& name, int number);
        virtual ~ChannelPanel();

        void addSlider(const wxString& name, SliderType type);

        void OnSliderChange(SliderType type, int value);

    protected:
        Processor* processor;
        int channel;

    private:
};

}; // namespace

#endif // CHANNELPANEL_H
