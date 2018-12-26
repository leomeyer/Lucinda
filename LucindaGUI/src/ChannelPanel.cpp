#include "ChannelPanel.h"

#include "SliderPanel.h"
#include "PercentSlider.h"
#include "FrequencySlider.h"

#include "Context.h"
#include "Controller.h"
#include "Processor.h"
#include "ColorManagement.h"
#include "UndoManager.h"

namespace APP_NAMESPACE {

ChannelPanel::ChannelPanel(wxWindow* parent, Controller* controller, const wxString& name, int number)
    : ChannelPanelBase(parent)
{
    this->controller = controller;
    this->context = controller->getContext();
    this->channel = number;

    wxString cName = name;
    cName << " (Channel " << number << ")";
    stChannelName->SetLabel(cName);

    startupButtonBackground = btnSend->GetBackgroundColour();

    loadPresets();
    settings.dirty = false;
    settings.validate();
    updateControls();
}

ChannelPanel::~ChannelPanel()
{
}

SliderPanel* ChannelPanel::addSlider(const wxString& name, SliderType type)
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
        default: return nullptr;
    }

    sliders.push_back(slider);

    sizerInternal->Add(slider, 0, wxALL | wxEXPAND, 1);

    wxSize cSize = GetClientSize();
    wxSize pSize = slider->GetMinSize();
    SetClientSize(wxSize(cSize.x + pSize.x, cSize.y));
    SetMinSize(wxSize(sliders.size() * pSize.x + 20, -1));

    return slider;
}

int ChannelPanel::getChannel()
{
    return channel;
}

const ChannelSettings* ChannelPanel::getSettings()
{
    return &settings;
}

void ChannelPanel::setSettings(const ChannelSettings& settings)
{
    applyUndoableChange(settings);
}

void ChannelPanel::sendSettings(bool apply)
{
    context->processor->OnSendChannelSettings(this);
    settings.dirty = false;
    settings.validate();
    updateControls();
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
    // context->undoManager->
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
        btnSend->SetBackgroundColour(*wxYELLOW);
    else
        btnSend->SetBackgroundColour(startupButtonBackground);
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

void ChannelPanel::setLightBit(ChannelSettings& localSettings, int lightNo) {
    if (localSettings.lights < 0) {
        localSettings.lights = 0;
        localSettings.enabled = true;
    }
    localSettings.lights |= 1 << lightNo;
}

void ChannelPanel::clearLightBit(ChannelSettings& localSettings, int lightNo) {
    localSettings.lights &= ~(1 << lightNo);
    if (localSettings.lights == 0)
        localSettings.lights = -1;
}

void ChannelPanel::OnCheckBox(wxCommandEvent& event)
{
    #define TEST_LIGHT_CHECKBOX(number)     if (event.GetEventObject() == cb##number) { \
        if (cb##number->GetValue()) \
            setLightBit(localSettings, (number - 1)); \
        else \
            clearLightBit(localSettings, (number - 1)); \
    }

    ChannelSettings localSettings = settings;

    localSettings.dirty = true;

    if (event.GetEventObject() == cbReverse) {
        localSettings.reverse = cbReverse->GetValue();
    }
    if (event.GetEventObject() == cbInvert) {
        localSettings.invert = cbInvert->GetValue();
    }
    if (event.GetEventObject() == cbEyeCorrection) {
        localSettings.eyeCorrection = cbEyeCorrection->GetValue();
    }
    if (event.GetEventObject() == cbEnabled) {
        localSettings.enabled = cbEnabled->GetValue();
    }
    if (event.GetEventObject() == cbHalogen) {
        if (cbHalogen->GetValue()) {
            localSettings.lights = 0;
            localSettings.enabled = true;
        } else
            localSettings.lights = -1;
    }
    TEST_LIGHT_CHECKBOX(1)
    TEST_LIGHT_CHECKBOX(2)
    TEST_LIGHT_CHECKBOX(3)
    TEST_LIGHT_CHECKBOX(4)
    TEST_LIGHT_CHECKBOX(5)
    TEST_LIGHT_CHECKBOX(6)
    TEST_LIGHT_CHECKBOX(7)
    TEST_LIGHT_CHECKBOX(8)

    applyUndoableChange(localSettings);
}

void ChannelPanel::OnCombobox(wxCommandEvent& event)
{
    ChannelSettings localSettings = settings;

    if (event.GetEventObject() == cmbWaveform)
        localSettings.waveform = (Waveform)cmbWaveform->GetSelection();

    applyUndoableChange(localSettings);
}

void ChannelPanel::setMulticycleValue(wxTextCtrl* ctrl)
{
    ChannelSettings localSettings = settings;

    uint8_t* target = nullptr;
    if (ctrl == txtMCLength)
        target = &localSettings.mcLength;
    else if (ctrl == txtMCCount)
        target = &localSettings.mcCount;
    else if (ctrl == txtMCShift)
        target = &localSettings.mcShift;
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

    applyUndoableChange(localSettings);
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

void ChannelPanel::OnSendAll(wxCommandEvent& event)
{
    controller->sendAllChannelSettings();
}

void ChannelPanel::OnSynchronize(wxCommandEvent& event)
{
    controller->synchronize();
}

void ChannelPanel::OnButtonSend(wxCommandEvent& event)
{
    sendSettings();
}

void ChannelPanel::OnButtonReset(wxCommandEvent& event)
{
    loadPresets();
    updateControls();
}


void ChannelPanel::undo(UndoChange* change)
{
    ChannelUndoInfo* data = (ChannelUndoInfo*)change->data;
    settings = data->previous;
    settings.dirty = true;
    settings.validate();
    updateControls();
}

void ChannelPanel::redo(UndoChange* change)
{
    ChannelUndoInfo* data = (ChannelUndoInfo*)change->data;
    settings = data->current;
    settings.dirty = true;
    settings.validate();
    updateControls();
}

void ChannelPanel::applyUndoableChange(ChannelSettings newSettings)
{
    if (newSettings != settings) {
        // register change, store previous and current slider value
        ChannelUndoInfo* data = new ChannelUndoInfo();
        data->previous = settings;
        data->current = newSettings;
        UndoChange* undoChange = new UndoChange(this, 0, stChannelName->GetLabel() + " Settings", data);

        context->undoManager->addUndoChange(undoChange);

        settings = newSettings;
        settings.validate();
        updateControls();
    }
}


}; // namespace
