#ifndef SLIDERPANEL_H
#define SLIDERPANEL_H

#include "GlobalDefines.h"

#include "../GUIFrame.h"


namespace APP_NAMESPACE {

class ChannelPanel;

class SliderPanel : public SliderPanelBase
{
    public:
        SliderPanel(ChannelPanel* channel, SliderType type, const wxString& name, int min, int max);
        virtual ~SliderPanel();

    protected:
        ChannelPanel* channel;
        SliderType type;

		virtual void OnFocusValue( wxFocusEvent& event );
        virtual void OnValueEnter( wxCommandEvent& event );     // enter key
   		virtual void OnSlider( wxCommandEvent& event );

   		void UpdateControls();

    private:
};

}; // namespace

#endif // SLIDERPANEL_H
