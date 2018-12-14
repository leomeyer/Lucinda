Lucinda Hypnagogic Light Machine Software

** Overview **

This project aims to create hardware and software that can be used to induce so-called hypnagogic light experiences. These experiences occur when flashing light pulses strike one's closed eyes while in a relaxed state. The experiences are sometimes described as exceptionally beautiful and  consist of mesmerizingly moving patterns and colors.

The current state of this project is pre-beta. There is little functionality available at the moment.

** Software **

Software in this project is written in C++.

The software consists of:
  - An Arduino IDE sketch designed to run on the Arduino Mega (ATmega 2560)
  - A cross-platform GUI to control the hardware
  - helper projects

** Hardware **

The Lucinda hardware consists of an Arduino Mega and a driver board that supports a MOSFET driven 12V 35 W halogen lamp and eight super bright LEDs.
  
** Arduino IDE sketch **

*** Compiling the sketch ***

The Arduino sketch requires the Arduino IDE 1.8.7 or compatible software to be installed.
To setup the sketch for compilation you need to copy the libraries from the following path:
./Arducom/src/slave/lib
to your Arduino IDE libraries folder before starting the IDE.
The location of this folder is platform dependent. On Windows it is usually found under
C:\Users\<username>\Documents\Arduino\libraries
See the Arduino documentation for other platforms.

*** Arduino sketch operation ***
The Arduino program runs an interrupt-driven loop at a frequency of 1024 Hz. One iteration is called a "tick", i. e. one tick is 1/1024 seconds long. This loop calculates the brightness value for up to nine channels. Each channel can control multiple lights. Different channels, however, will typically control different lights. The first channel, channel 0, is by convention reserved for controlling the halogen lamp which is connected to the first defined pin (pin 11 if using the standard wiring). The other channels are used to combine the LEDs into patterns that can be individually controlled. A pattern combination is not fixed. It can be changed by the control software at any time.

A channel supports a number of parameters that can be individually controlled to determine the behavior of the connected LEDs. These properties are:

- enabled: 1 or 0. Determines whether the channel is enabled or not. A disabled channel's lights are switched off.
- bitmask for the lights. 8 bit value. Determins the pins controlled by this channel. If this value is 0 it controls the first pin which by convention is connected to the halogen lamp. If any bit is set it corresponds to the respective output pin. The lowest bit means the first pin.
- period. 16 bit value. The length of a "waveform cycle" in 1/1024 of a second. This value determines the flashing frequency of the connected lights. It is limited to 10240 which corresponds to a frequency of 0.1 Hz or one cycle every ten seconds. If the period is 0 the channel value will be set to the minimum brightness value. The value 1 will for instance set the channel frequency to 512 Hz.
- offset: 0 to 255. The minimum brightness value. The output values will never be lower than this value (except in case of inversion).
- channel brightness: 0 to 255. Is used to scale the channel's brightness. A value of 127, for example, will set the brightness to 50%.
- duty cycle. 0 to 255. A duty cycle of 0 means that the lights will always be at the minimum brightness value (0%). The value of 255 corresponds to 100% duty cycle. If the waveform is square, for example, this means that the lights will always be at maximum brightness. If the value is 127, i. e. a duty cycle of 50%, this means that a full iteration through the waveform will be exactly half of the period long. The brightness will be at minimum value for the rest of the period.
- phase shift: 16 bit value. The "position" within the period at which the duty cycle starts. Will automatically be "wrapped around" the period length (modulo calculation), e. i when the period is 1024 and the phase shift is set to 1025, the actual phase shift will become 1. A check mechanism ensures that the phase shift doesn't cause the phase to start right in the middle of a waveform; instead, the waveform will start to become effective at the regular start of a phase to avoid uncontrolled flickering.
- waveform: 0 to 4. 0: square, 1: sine, 2: triangle, 3: flicker, 4: linear/sawtooth
- flags: 8 bit value. The flags control the following behaviors:
  - whether to use the logarithmic eye correction factor
  - channel inversion (swap minimum and maximum brighness)
  - waveform reversal (only useful for asymmetric waveforms such as sawtooth)
- macrocycle length: 8 bit value. The number of periods that make up a macrocycle. If it is 0 or 1 macrocycling is not active.
- macrocycle count: 8 bit value. The number of flashes within the macrocycle. The lights will be at the minimum brightness value for all other macrocycles.
- macrocycle shift: 8 bit value. The number of macrocycles to pass before flashing the lights.

A special command allows setting all these values at once.

Global settings:
- speed: The increment of the timer loop. This value is normally 1. By setting it to a higher value all channels can be sped up by a factor of two, three etc. Setting the speed to 0 will disable all channels and set all their outputs to 0. This value can therefore be used to switch all lights off.
- global brightness: This value applies to all channels simultaneously and can be used to smoothly fade in and out all lights.

An important aspect is the synchronization of the lights. The hypnagogic experience should be repeatable, without any random effects. As the sketch is controlled by outside machinery (i. e. a PC via RS232) which might be subject to uncontrollable jitter or timing differences, care must be taken that all channels operate synchronously as intended. Therefore some properties of a channel should only be changed at the end of a period. This also ensures smooth operation. For example, changing the waveform suddenly might lead to uncontrollable flickering of lights which could interfere with a pleasant user experience. This behavior can be overridden, though.

Channel properties that can be changed at all times are:
- enabled
- offset (minimum brightness)
- channel brightness
- duty cycle

All other properties can be changed at any time but this change will normally only take effect after a complete period has elapsed. This means that for periods of longer duration you might have to wait for quite some time. An exception applies when the global speed is set to 0, i. e. lights are disabled. In this state all channel changes are applied directly. All channel periods and macrocycles will start at the beginning when the speed value is set to a value greater than 0. So, for a controlled reconfiguration of all channels you would have to follow this suggested sequence:
- perhaps fade out everything using the global brightness value
- set global speed to 0, thereby disabling all lights
- reconfigure the channels
- set global speed to 1 to enable lights and start over all periods and macrocycles
- set the global brightness to the desired value

When a channel becomes enabled its period and macrocycle counters will start from 0.


