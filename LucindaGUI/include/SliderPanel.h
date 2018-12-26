#ifndef SLIDERPANEL_H
#define SLIDERPANEL_H

#include "GlobalDefines.h"

#include "../GUIFrame.h"

namespace APP_NAMESPACE {

class ChannelPanel;

class SliderPanel : public SliderPanelBase, public IUndoRedoable
{
    public:

        SliderPanel(wxWindow* parent, ChannelPanel* channel, SliderType type, const wxString& name, int min, int max, int value,
                    const wxColour* colour = nullptr);

        virtual ~SliderPanel();

        void setSliderValue(int value);

        SliderType getType();

        uint16_t getValue();

        void undo(UndoChange* change) override;

        void redo(UndoChange* change) override;

    protected:
        class SliderUndoInfo: public UndoInfo {
        public:
            int previous;
            int current;
        };

        ChannelPanel* channel;
        SliderType type;
        int min;
        int max;
        int currentValue;
        int preTrackValue;

        virtual int getDeviceValue(int sliderValue);

        virtual wxString valueToString(const int value);

        virtual bool stringToValue(const wxString& str, int& value);

   		virtual void setLabels();

   		virtual void updateControls();

   		void applyUndoableChange(int value);

    private:
        virtual void OnValCharHook(wxKeyEvent& event) override;
		virtual void OnFocusValue( wxFocusEvent& event ) override;
        virtual void OnValueEnter( wxCommandEvent& event ) override;     // enter key
		virtual void OnSliderRelease( wxScrollEvent& event ) override;
		virtual void OnSliderTrack( wxScrollEvent& event ) override;
   		virtual void OnSlider( wxCommandEvent& event ) override;
};

}; // namespace

#endif // SLIDERPANEL_H
