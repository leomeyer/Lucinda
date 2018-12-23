#include "ChannelPanel.h"

#include "SliderPanel.h"
#include "PercentSlider.h"
#include "FrequencySlider.h"

#include "Context.h"
#include "Processor.h"
#include "ColorManagement.h"

namespace APP_NAMESPACE {

ChannelPanel::ChannelPanel(wxWindow* parent, Context* context, const wxString& name, int number)
    : ChannelPanelBase(parent)
{
    this->context = context;
    this->channel = number;

    wxString cName = name;
    cName << " (Channel " << number << ")";
    stChannelName->SetLabel(cName);

    startupButtonBackground = btnSet->GetBackgroundColour();

    loadPresets();
    settings.dirty = false;
    settings.validate();
    updateControls();
}

ChannelPanel::~ChannelPanel()
{
}

void ChannelPanel::addSlider(const wxString& name, SliderType type)
{
    // construct slider depending on type
    SliderPanel* slider;
    switch (type) {
        case SLIDER_BRIGHTNESS: slider = new PercentSlider(pInternal, this, type, name, 127,
                                                           context->colorManagement->getBrightnessColor()); break;
        case SLIDER_GLOBAL_SPEED: slider = new SliderPanel(pInternal, this, type, name, 0, GLOBAL_SPEED_MAX, 1,
                                                           context->colorManagement->getFrequencyColor()); break;
        case SLIDER_PERIOD: slider = new FrequencySlider(pInternal, this, type, name, CHANNEL_PERIOD_MAX, 89,
                                                         context->colorManagement->getFrequencyColor()); break;
        case SLIDER_PHASESHIFT: slider = new PercentSlider(pInternal, this, type, name, 0,
                                                           context->colorManagement->getPhaseshiftColor()); break;
        case SLIDER_OFFSET: slider = new PercentSlider(pInternal, this, type, name, 0,
                                                       context->colorManagement->getOffsetColor()); break;
        case SLIDER_DUTYCYCLE: slider = new PercentSlider(pInternal, this, type, name, 255,
                                                          context->colorManagement->getDutycycleColor()); break;
        default: return;
    }

    sliders.push_back(slider);

    sizerInternal->Add(slider, 0, wxALL | wxEXPAND, 1);

    wxSize cSize = GetClientSize();
    wxSize pSize = slider->GetMinSize();
    SetClientSize(wxSize(cSize.x + pSize.x, cSize.y));
    SetMinSize(wxSize(sliders.size() * pSize.x + 20, -1));

    //channelSizer->Fit(pInternal);
}

int ChannelPanel::getChannel()
{
    return channel;
}

const ChannelSettings* ChannelPanel::getSettings()
{
    return &settings;
}

uint16_t ChannelPanel::getPeriod()
{
    return getSliderValue(SliderType::SLIDER_PERIOD, 1024);
}

uint8_t ChannelPanel::getBrightness()
{
    return getSliderValue(SliderType::SLIDER_BRIGHTNESS, 127);
}

uint8_t ChannelPanel::getOffset()
{
    return getSliderValue(SliderType::SLIDER_OFFSET, 0);
}

uint8_t ChannelPanel::getPhaseshift()
{
    return getSliderValue(SliderType::SLIDER_PHASESHIFT, 0);
}

uint8_t ChannelPanel::getDutyCycle()
{
    return getSliderValue(SliderType::SLIDER_DUTYCYCLE, 255);
}

uint16_t ChannelPanel::getSliderValue(SliderType type, uint16_t defaultValue)
{
    // find the slider
    auto end = sliders.end();
    for (auto iter = sliders.begin(); iter != end; ++iter) {
        if ((*iter)->getType() == type)
            return (*iter)->getValue();
    }
    return defaultValue;
}


void ChannelPanel::OnSliderChange(SliderType type, int value)
{
    context->processor->OnValueChange(channel, type, value);
}

void ChannelPanel::updateControls()
{
    // update light checkboxes
    cbHalogen->SetValue(false);
    cb1->SetValue(false);
    cb2->SetValue(false);
    cb3->SetValue(false);
    cb4->SetValue(false);
    cb5->SetValue(false);
    cb6->SetValue(false);
    cb7->SetValue(false);
    cb8->SetValue(false);
    if (settings.lights == 0) {
        cbHalogen->SetValue(true);
        cbEnabled->Enable(true);
    } else if (settings.lights > 0) {
        cb1->SetValue((1 & settings.lights) != 0);
        cb2->SetValue((2 & settings.lights) != 0);
        cb3->SetValue((4 & settings.lights) != 0);
        cb4->SetValue((8 & settings.lights) != 0);
        cb5->SetValue((16 & settings.lights) != 0);
        cb6->SetValue((32 & settings.lights) != 0);
        cb7->SetValue((64 & settings.lights) != 0);
        cb8->SetValue((128 & settings.lights) != 0);
        cbEnabled->Enable(true);
    } else {
        // no lights set, disable "enabled" checkbox
        cbEnabled->Enable(false);
    }

    cbEnabled->SetValue(settings.enabled);
    cmbWaveform->SetSelection(settings.waveform);
    cbReverse->SetValue(settings.reverse);
    cbInvert->SetValue(settings.invert);
    cbEyeCorrection->SetValue(settings.eyeCorrection);
    txtMCLength->SetValue(std::to_string(settings.mcLength));
    txtMCCount->SetValue(std::to_string(settings.mcCount));
    txtMCShift->SetValue(std::to_string(settings.mcShift));

    if (settings.dirty)
        btnSet->SetBackgroundColour(*wxYELLOW);
    else
        btnSet->SetBackgroundColour(startupButtonBackground);
}

void ChannelPanel::loadPresets()
{
    settings.dirty |= settings.lights != -1;
    settings.lights = -1;  // no lights
    settings.dirty |= settings.enabled != false;
    settings.enabled = false;
    settings.dirty |= settings.waveform != WAVEFORM_SINE;
    settings.waveform = WAVEFORM_SINE;
    settings.dirty |= settings.reverse != false;
    settings.reverse = false;
    settings.dirty |= settings.invert != false;
    settings.invert = false;
    settings.dirty |= settings.eyeCorrection != true;
    settings.eyeCorrection = true;
    settings.dirty |= settings.mcLength != 0;
    settings.mcLength = 0;
    settings.dirty |= settings.mcCount != 0;
    settings.mcCount = 0;
    settings.dirty |= settings.mcShift != 0;
    settings.mcShift = 0;

    settings.validate();
}

UndoAction ChannelPanel::createUndoAction()
{
    return UndoAction();
}

void ChannelPanel::setLightBit(int lightNo) {
    if (settings.lights < 0) {
        settings.lights = 0;
        settings.enabled = true;
    }
    settings.lights |= 1 << lightNo;
}

void ChannelPanel::clearLightBit(int lightNo) {
    settings.lights &= ~(1 << lightNo);
    if (settings.lights == 0)
        settings.lights = -1;
}

void ChannelPanel::OnCheckBox(wxCommandEvent& event)
{
    #define TEST_LIGHT_CHECKBOX(number)     if (event.GetEventObject() == cb##number) { \
        if (cb##number->GetValue()) \
            setLightBit((number - 1)); \
        else \
            clearLightBit((number - 1)); \
    }

    settings.dirty = true;

    if (event.GetEventObject() == cbReverse) {
        settings.reverse = cbReverse->GetValue();
    }
    if (event.GetEventObject() == cbInvert) {
        settings.invert = cbInvert->GetValue();
    }
    if (event.GetEventObject() == cbEyeCorrection) {
        settings.eyeCorrection = cbEyeCorrection->GetValue();
    }
    if (event.GetEventObject() == cbEnabled) {
        settings.enabled = cbEnabled->GetValue();
    }
    if (event.GetEventObject() == cbHalogen) {
        if (cbHalogen->GetValue()) {
            settings.lights = 0;
            settings.enabled = true;
        } else
            settings.lights = -1;
    }
    TEST_LIGHT_CHECKBOX(1)
    TEST_LIGHT_CHECKBOX(2)
    TEST_LIGHT_CHECKBOX(3)
    TEST_LIGHT_CHECKBOX(4)
    TEST_LIGHT_CHECKBOX(5)
    TEST_LIGHT_CHECKBOX(6)
    TEST_LIGHT_CHECKBOX(7)
    TEST_LIGHT_CHECKBOX(8)

    settings.validate();
    updateControls();
}

void ChannelPanel::OnCombobox(wxCommandEvent& event)
{
    if (event.GetEventObject() == cmbWaveform)
        settings.waveform = (Waveform)cmbWaveform->GetSelection();

    settings.validate();
    updateControls();
}

void ChannelPanel::setMulticycleValue(wxTextCtrl* ctrl)
{
    uint8_t* target = nullptr;
    if (ctrl == txtMCLength)
        target = &settings.mcLength;
    else if (ctrl == txtMCCount)
        target = &settings.mcCount;
    else if (ctrl == txtMCShift)
        target = &settings.mcShift;
    if (target == nullptr)
        return;

    long lvalue;
    if (ctrl->GetValue().ToLong(&lvalue)) {
        if (lvalue > MULTICYCLE_MAX_VALUE)
            lvalue = MULTICYCLE_MAX_VALUE;
        if (lvalue < 0)
            lvalue = 0;

        *target = (uint8_t)lvalue;
    }

    settings.validate();
    updateControls();
}

void ChannelPanel::OnTextKillFocus(wxFocusEvent& event)
{
    setMulticycleValue((wxTextCtrl*)event.GetEventObject());
    event.Skip();
}

void ChannelPanel::OnTextEnter(wxCommandEvent& event)
{
    setMulticycleValue((wxTextCtrl*)event.GetEventObject());
}

void ChannelPanel::OnText(wxCommandEvent& event)
{
}

void ChannelPanel::OnButtonSet(wxCommandEvent& event)
{
    context->processor->OnSetChannelSettings(this);
    settings.dirty = false;
    settings.validate();
    updateControls();
}

void ChannelPanel::OnButtonReset(wxCommandEvent& event)
{
    loadPresets();
    updateControls();
}


}; // namespace
