#ifndef SLIDERPANEL_H
#define SLIDERPANEL_H

#include "GlobalDefines.h"

#include "../GUIFrame.h"
#include "ChannelPanel.h"

namespace APP_NAMESPACE {

class SliderPanel : public SliderPanelBase
{
    public:

        SliderPanel(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int min, int max);

        virtual ~SliderPanel();

    protected:
        ChannelPanel* channel;
        SliderType type;
        int min;
        int max;

       virtual int getDeviceValue(int sliderValue);

        virtual wxString valueToString(const int value);

        virtual bool stringToValue(const wxString& str, int& value);

   		virtual void setLabels();

   		void updateControls();

    private:
		virtual void OnFocusValue( wxFocusEvent& event );
        virtual void OnValueEnter( wxCommandEvent& event );     // enter key
   		virtual void OnSlider( wxCommandEvent& event );
};

}; // namespace

#endif // SLIDERPANEL_H
