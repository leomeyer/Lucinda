// Lucinda v2
// by Leo Meyer <leo@leomeyer.de>

#include <Arducom.h>
#include <ArducomStream.h>

/*******************************************************
* Data Structures
*******************************************************/

// Defines how the output pins map to PWM registers.
// This table is filled at setup from the information in outputPins.
timermap_t timerMaps[LUCINDA_MAXCHANNELS];

// Holds the PWM definition and counter for each channel.
channel_t channels[LUCINDA_MAXCHANNELS];

/*******************************************************
* Constants
*******************************************************/

// Defines the pins of the connected lamps.
// The first pin is for the halogen lamp.
// The others are for the LEDs. If a lamp is not connected use 0.
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 0, 0, 0, 0, 0, 0, 0, 0};

/*******************************************************
* Arducom commands
*******************************************************/

// This command returns the configuration of the Lucinda setup.
class ArducomGetConfig: public ArducomCommand {
public:
  ArducomGetConfig(uint8_t commandCode) : ArducomCommand(commandCode, 0) {}   // this command expects zero parameters
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    const char* configStr = "Cl";
    strncpy((char*)destBuffer, configStr, maxBufferSize);
    destBuffer[1] = '0' + LUCINDA_MAXCHANNELS;
    *dataSize = strlen((const char*)destBuffer);
    return ARDUCOM_OK;
  }
};

// This command defines the configuration of a channel.
// It expects the following parameters:
// byte 1: channel number (may be 0 - 8)
// byte 2: bit mask for the outputs. Each bit corresponds to an LED. If no bit is set the channel is for the halogen lamp.
// byte 3: enabled flag. The channel is used if the flag is 1.
class ArducomDefineChannel: public ArducomCommand {
public:
  ArducomDefineChannel(uint8_t commandCode) : ArducomCommand(commandCode, 3) {}   // number of expected parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    uint8_t bitmask = dataBuffer[1];
    uint8_t enabled = dataBuffer[2] & 0x01; // the lowest bit decides
    channels[channelNo].enabled = enabled;
    channels[channelNo].bitmask = bitmask;
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};


/*******************************************************
* Variables
*******************************************************/

// Arducom system variables
ArducomTransportStream arducomTransport(&Serial);
Arducom arducom(&arducomTransport);

/*******************************************************
* Setup
*******************************************************/

void fillTimerMaps() {
  for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
    if (outputPins[i] == 0)
      continue;
    if (!fillTimerMap(&(timerMaps[i]), outputPins[i])) {
      Serial.print("Setup error: Pin not on timer: ");
      Serial.println(outputPins[i]);
      while(true);
    }
  }
}

uint8_t addCommand(ArducomCommand* cmd) {
  uint8_t code = arducom.addCommand(cmd);
  if (code != ARDUCOM_OK) {
    Serial.print("Setup error: Error adding command: ");
    Serial.print((int)cmd->commandCode);
    Serial.print(" (");
    Serial.print(code);
    Serial.println(")");
    while(true);
  }
}

/*
#define setupCommand(c) \
  code = arducom.addCommand(c); \
  if (code != ARDUCOM_OK) { \
    Serial.print("Setup error: Error adding command: "); \
    Serial.print((int)c->commandCode); \
    Serial.print(" ("); \
    Serial.print(code); \
    Serial.println(")"); \
    while(true); \
  }
*/
void setup()
{	
	// initialize hardware
	Serial.begin(57600);

  Serial.println(APP_NAME);

  fillTimerMaps();

  uint8_t code;
	// setup Arducom system
  addCommand(new ArducomVersionCommand(APP_NAME));
  addCommand(new ArducomGetConfig(ARDUCOM_COMMAND_GETCONFIG));
  addCommand(new ArducomDefineChannel(ARDUCOM_COMMAND_DEFINECHANNEL));

  Serial.println("Setup complete.");
}

/*******************************************************
* Main loop
*******************************************************/

void loop()
{
	// handle Arducom commands
	arducom.doWork();
}
