#ifndef CHANNELPANEL_H
#define CHANNELPANEL_H

#include "GlobalDefines.h"
#include "UndoManager.h"

#include "../GUIFrame.h"

namespace APP_NAMESPACE {

class Processor;
class SliderPanel;

enum Waveform
{
    WAVEFORM_SQUARE,
    WAVEFORM_SINE,
    WAVEFORM_TRIANGLE,
    WAVEFORM_FLICKER,
    WAVEFORM_LINEAR
};

#define MULTICYCLE_MAX_VALUE 100

struct ChannelSettings
{
    int lights;
    bool enabled;
    Waveform waveform;
    bool reverse;
    bool invert;
    bool eyeCorrection;
    uint8_t mcLength;
    uint8_t mcCount;
    uint8_t mcShift;

    bool dirty;

    void validate()
    {
        // if no lights are set the channel becomes disabled
        if (lights == -1)
            enabled = false;

        if (mcLength > MULTICYCLE_MAX_VALUE)
            mcLength = MULTICYCLE_MAX_VALUE;
        if (mcCount > mcLength)
            mcCount = mcLength;
        if (mcLength == 0)
            mcShift = 0;
        else
            if (mcShift > mcLength - 1)
                mcShift = mcLength - 1;
    }

    uint8_t getDeviceBitmask() const
    {
        if (lights < 0)
            return 0;
        else
            return lights;
    }
};

class ChannelPanel : public ChannelPanelBase
{
    public:
        ChannelPanel(wxWindow* parent, Processor* processor, const wxString& name, int number);
        virtual ~ChannelPanel();

        void addSlider(const wxString& name, SliderType type);

        void OnSliderChange(SliderType type, int value);

        int getChannel();
        const ChannelSettings* getSettings();

        uint16_t getPeriod();
        uint8_t getBrightness();
        uint8_t getOffset();
        uint8_t getPhaseshift();
        uint8_t getDutyCycle();

    protected:
        Processor* processor;
        int channel;
        ChannelSettings settings;
        wxVector<SliderPanel*> sliders;
        wxColour startupButtonBackground;

        UndoAction createUndoAction();

        uint16_t getSliderValue(SliderType type, uint16_t defaultValue);

        void setLightBit(int lightNo);
        void clearLightBit(int lightNo);

        void updateControls();

        void loadPresets();

        void setMulticycleValue(wxTextCtrl* ctrl);

		virtual void OnCheckBox( wxCommandEvent& event ) override;
		virtual void OnCombobox( wxCommandEvent& event ) override;
		virtual void OnTextKillFocus( wxFocusEvent& event ) override;
		virtual void OnText( wxCommandEvent& event ) override;
		virtual void OnTextEnter( wxCommandEvent& event ) override;
		virtual void OnButtonSet( wxCommandEvent& event ) override;
		virtual void OnButtonReset( wxCommandEvent& event ) override;

    private:
};

}; // namespace

#endif // CHANNELPANEL_H
