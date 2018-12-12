// Lucinda v2
// by Leo Meyer <leo@leomeyer.de>

#include <Arducom.h>
#include <ArducomStream.h>

// #define LUCINDA_DEBUG 1

// for some reason this forward declaration is necessary
void addCommand(ArducomCommand* cmd);
//extern wavetable_t WAVE_SINE;     // defined in tables.cpp

/*******************************************************
* Data Structures
*******************************************************/

// Defines how the output pins map to PWM registers.
// This table is filled at setup from the information in outputPins.
timermap_t timerMaps[LUCINDA_MAXCHANNELS];

// Holds the PWM definition and counter for each channel.
channel_t channels[LUCINDA_MAXCHANNELS];

volatile uint8_t global_brightness = 255;
volatile uint8_t global_speed = 1;

/*******************************************************
* Constants
*******************************************************/

// Defines the pins of the connected lamps.
// The first pin is for the halogen lamp.
// The others are for the LEDs. If a lamp is not connected use 0.
#if defined(__AVR_ATmega2560__)
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 2, 3, 4, 5, 6, 7, 8, 9};
#else
uint8_t outputPins[LUCINDA_MAXCHANNELS] = {11, 3, 5, 6, 9, 10, 0, 0, 0};
#endif

PROGMEM const wavetable_t WAVE_SINE = {
0, 0, 1, 2, 3, 3, 4, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 18, 19, 20, 21, 21, 22, 23, 24, 25, 
25, 26, 27, 28, 28, 29, 30, 31, 32, 32, 33, 34, 35, 36, 36, 37, 38, 39, 39, 40, 41, 42, 42, 43, 44, 45, 46, 46, 47, 48, 49, 49, 
50, 51, 52, 53, 53, 54, 55, 56, 56, 57, 58, 59, 59, 60, 61, 62, 62, 63, 64, 65, 66, 66, 67, 68, 69, 69, 70, 71, 72, 72, 73, 74, 
75, 75, 76, 77, 78, 78, 79, 80, 81, 81, 82, 83, 84, 84, 85, 86, 86, 87, 88, 89, 89, 90, 91, 92, 92, 93, 94, 95, 95, 96, 97, 97, 
98, 99, 100, 100, 101, 102, 103, 103, 104, 105, 105, 106, 107, 108, 108, 109, 110, 110, 111, 112, 112, 113, 114, 115, 115, 116, 117, 117, 118, 119, 119, 120, 
121, 122, 122, 123, 124, 124, 125, 126, 126, 127, 128, 128, 129, 130, 130, 131, 132, 132, 133, 134, 134, 135, 136, 136, 137, 138, 138, 139, 140, 140, 141, 142, 
142, 143, 144, 144, 145, 146, 146, 147, 148, 148, 149, 149, 150, 151, 151, 152, 153, 153, 154, 155, 155, 156, 156, 157, 158, 158, 159, 159, 160, 161, 161, 162, 
163, 163, 164, 164, 165, 166, 166, 167, 167, 168, 168, 169, 170, 170, 171, 171, 172, 173, 173, 174, 174, 175, 175, 176, 177, 177, 178, 178, 179, 179, 180, 181, 
181, 182, 182, 183, 183, 184, 184, 185, 185, 186, 187, 187, 188, 188, 189, 189, 190, 190, 191, 191, 192, 192, 193, 193, 194, 194, 195, 195, 196, 196, 197, 197, 
198, 198, 199, 199, 200, 200, 201, 201, 202, 202, 203, 203, 204, 204, 205, 205, 206, 206, 207, 207, 207, 208, 208, 209, 209, 210, 210, 211, 211, 211, 212, 212, 
213, 213, 214, 214, 215, 215, 215, 216, 216, 217, 217, 217, 218, 218, 219, 219, 219, 220, 220, 221, 221, 221, 222, 222, 223, 223, 223, 224, 224, 225, 225, 225, 
226, 226, 226, 227, 227, 227, 228, 228, 229, 229, 229, 230, 230, 230, 231, 231, 231, 232, 232, 232, 233, 233, 233, 234, 234, 234, 234, 235, 235, 235, 236, 236, 
236, 237, 237, 237, 237, 238, 238, 238, 239, 239, 239, 239, 240, 240, 240, 241, 241, 241, 241, 242, 242, 242, 242, 243, 243, 243, 243, 244, 244, 244, 244, 244, 
245, 245, 245, 245, 246, 246, 246, 246, 246, 247, 247, 247, 247, 247, 248, 248, 248, 248, 248, 249, 249, 249, 249, 249, 249, 250, 250, 250, 250, 250, 250, 251, 
251, 251, 251, 251, 251, 251, 252, 252, 252, 252, 252, 252, 252, 252, 253, 253, 253, 253, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 
254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 254, 
254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 253, 253, 253, 253, 253, 252, 252, 252, 252, 252, 252, 252, 252, 251, 251, 251, 251, 251, 251, 251, 
250, 250, 250, 250, 250, 250, 249, 249, 249, 249, 249, 249, 248, 248, 248, 248, 248, 247, 247, 247, 247, 247, 246, 246, 246, 246, 246, 245, 245, 245, 245, 244, 
244, 244, 244, 244, 243, 243, 243, 243, 242, 242, 242, 242, 241, 241, 241, 241, 240, 240, 240, 239, 239, 239, 239, 238, 238, 238, 237, 237, 237, 237, 236, 236, 
236, 235, 235, 235, 234, 234, 234, 234, 233, 233, 233, 232, 232, 232, 231, 231, 231, 230, 230, 230, 229, 229, 229, 228, 228, 227, 227, 227, 226, 226, 226, 225, 
225, 225, 224, 224, 223, 223, 223, 222, 222, 221, 221, 221, 220, 220, 219, 219, 219, 218, 218, 217, 217, 217, 216, 216, 215, 215, 215, 214, 214, 213, 213, 212, 
212, 211, 211, 211, 210, 210, 209, 209, 208, 208, 207, 207, 207, 206, 206, 205, 205, 204, 204, 203, 203, 202, 202, 201, 201, 200, 200, 199, 199, 198, 198, 197, 
197, 196, 196, 195, 195, 194, 194, 193, 193, 192, 192, 191, 191, 190, 190, 189, 189, 188, 188, 187, 187, 186, 185, 185, 184, 184, 183, 183, 182, 182, 181, 181, 
180, 179, 179, 178, 178, 177, 177, 176, 175, 175, 174, 174, 173, 173, 172, 171, 171, 170, 170, 169, 168, 168, 167, 167, 166, 166, 165, 164, 164, 163, 163, 162, 
161, 161, 160, 159, 159, 158, 158, 157, 156, 156, 155, 155, 154, 153, 153, 152, 151, 151, 150, 149, 149, 148, 148, 147, 146, 146, 145, 144, 144, 143, 142, 142, 
141, 140, 140, 139, 138, 138, 137, 136, 136, 135, 134, 134, 133, 132, 132, 131, 130, 130, 129, 128, 128, 127, 126, 126, 125, 124, 124, 123, 122, 122, 121, 120, 
119, 119, 118, 117, 117, 116, 115, 115, 114, 113, 113, 112, 111, 110, 110, 109, 108, 108, 107, 106, 105, 105, 104, 103, 103, 102, 101, 100, 100, 99, 98, 97, 
97, 96, 95, 95, 94, 93, 92, 92, 91, 90, 89, 89, 88, 87, 86, 86, 85, 84, 84, 83, 82, 81, 81, 80, 79, 78, 78, 77, 76, 75, 75, 74, 
73, 72, 72, 71, 70, 69, 69, 68, 67, 66, 66, 65, 64, 63, 62, 62, 61, 60, 59, 59, 58, 57, 56, 56, 55, 54, 53, 53, 52, 51, 50, 49, 
49, 48, 47, 46, 46, 45, 44, 43, 43, 42, 41, 40, 39, 39, 38, 37, 36, 36, 35, 34, 33, 32, 32, 31, 30, 29, 29, 28, 27, 26, 25, 25, 
24, 23, 22, 21, 21, 20, 19, 18, 18, 17, 16, 15, 14, 14, 13, 12, 11, 11, 10, 9, 8, 7, 7, 6, 5, 4, 3, 3, 2, 1, 0
};

PROGMEM const wavetable_t WAVE_TRIANGLE = {
0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 
16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 
32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 
48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63, 
64, 64, 65, 65, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71, 72, 72, 73, 73, 74, 74, 75, 75, 76, 76, 77, 77, 78, 78, 79, 79, 
80, 80, 81, 81, 82, 82, 83, 83, 84, 84, 85, 85, 86, 86, 87, 87, 88, 88, 89, 89, 90, 90, 91, 91, 92, 92, 93, 93, 94, 94, 95, 95, 
96, 96, 97, 97, 98, 98, 99, 99, 100, 100, 101, 101, 102, 102, 103, 103, 104, 104, 105, 105, 106, 106, 107, 107, 108, 108, 109, 109, 110, 110, 111, 111, 
112, 112, 113, 113, 114, 114, 115, 115, 116, 116, 117, 117, 118, 118, 119, 119, 120, 120, 121, 121, 122, 122, 123, 123, 124, 124, 125, 125, 126, 126, 127, 127, 
127, 128, 128, 129, 129, 130, 130, 131, 131, 132, 132, 133, 133, 134, 134, 135, 135, 136, 136, 137, 137, 138, 138, 139, 139, 140, 140, 141, 141, 142, 142, 143, 
143, 144, 144, 145, 145, 146, 146, 147, 147, 148, 148, 149, 149, 150, 150, 151, 151, 152, 152, 153, 153, 154, 154, 155, 155, 156, 156, 157, 157, 158, 158, 159, 
159, 160, 160, 161, 161, 162, 162, 163, 163, 164, 164, 165, 165, 166, 166, 167, 167, 168, 168, 169, 169, 170, 170, 171, 171, 172, 172, 173, 173, 174, 174, 175, 
175, 176, 176, 177, 177, 178, 178, 179, 179, 180, 180, 181, 181, 182, 182, 183, 183, 184, 184, 185, 185, 186, 186, 187, 187, 188, 188, 189, 189, 190, 190, 191, 
191, 192, 192, 193, 193, 194, 194, 195, 195, 196, 196, 197, 197, 198, 198, 199, 199, 200, 200, 201, 201, 202, 202, 203, 203, 204, 204, 205, 205, 206, 206, 207, 
207, 208, 208, 209, 209, 210, 210, 211, 211, 212, 212, 213, 213, 214, 214, 215, 215, 216, 216, 217, 217, 218, 218, 219, 219, 220, 220, 221, 221, 222, 222, 223, 
223, 224, 224, 225, 225, 226, 226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 231, 232, 232, 233, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238, 239, 
239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 
254, 254, 253, 253, 252, 252, 251, 251, 250, 250, 249, 249, 248, 248, 247, 247, 246, 246, 245, 245, 244, 244, 243, 243, 242, 242, 241, 241, 240, 240, 239, 239, 
238, 238, 237, 237, 236, 236, 235, 235, 234, 234, 233, 233, 232, 232, 231, 231, 230, 230, 229, 229, 228, 228, 227, 227, 226, 226, 225, 225, 224, 224, 223, 223, 
222, 222, 221, 221, 220, 220, 219, 219, 218, 218, 217, 217, 216, 216, 215, 215, 214, 214, 213, 213, 212, 212, 211, 211, 210, 210, 209, 209, 208, 208, 207, 207, 
206, 206, 205, 205, 204, 204, 203, 203, 202, 202, 201, 201, 200, 200, 199, 199, 198, 198, 197, 197, 196, 196, 195, 195, 194, 194, 193, 193, 192, 192, 191, 191, 
190, 190, 189, 189, 188, 188, 187, 187, 186, 186, 185, 185, 184, 184, 183, 183, 182, 182, 181, 181, 180, 180, 179, 179, 178, 178, 177, 177, 176, 176, 175, 175, 
174, 174, 173, 173, 172, 172, 171, 171, 170, 170, 169, 169, 168, 168, 167, 167, 166, 166, 165, 165, 164, 164, 163, 163, 162, 162, 161, 161, 160, 160, 159, 159, 
158, 158, 157, 157, 156, 156, 155, 155, 154, 154, 153, 153, 152, 152, 151, 151, 150, 150, 149, 149, 148, 148, 147, 147, 146, 146, 145, 145, 144, 144, 143, 143, 
142, 142, 141, 141, 140, 140, 139, 139, 138, 138, 137, 137, 136, 136, 135, 135, 134, 134, 133, 133, 132, 132, 131, 131, 130, 130, 129, 129, 128, 128, 127, 127, 
127, 126, 126, 125, 125, 124, 124, 123, 123, 122, 122, 121, 121, 120, 120, 119, 119, 118, 118, 117, 117, 116, 116, 115, 115, 114, 114, 113, 113, 112, 112, 111, 
111, 110, 110, 109, 109, 108, 108, 107, 107, 106, 106, 105, 105, 104, 104, 103, 103, 102, 102, 101, 101, 100, 100, 99, 99, 98, 98, 97, 97, 96, 96, 95, 
95, 94, 94, 93, 93, 92, 92, 91, 91, 90, 90, 89, 89, 88, 88, 87, 87, 86, 86, 85, 85, 84, 84, 83, 83, 82, 82, 81, 81, 80, 80, 79, 
79, 78, 78, 77, 77, 76, 76, 75, 75, 74, 74, 73, 73, 72, 72, 71, 71, 70, 70, 69, 69, 68, 68, 67, 67, 66, 66, 65, 65, 64, 64, 63, 
63, 62, 62, 61, 61, 60, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 53, 52, 52, 51, 51, 50, 50, 49, 49, 48, 48, 47, 
47, 46, 46, 45, 45, 44, 44, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 37, 37, 36, 36, 35, 35, 34, 34, 33, 33, 32, 32, 31, 
31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26, 25, 25, 24, 24, 23, 23, 22, 22, 21, 21, 20, 20, 19, 19, 18, 18, 17, 17, 16, 16, 15, 
15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0
};

PROGMEM const wavetable_t WAVE_FLICKER = {
0, 143, 49, 206, 149, 122, 89, 228, 209, 190, 44, 219, 181, 130, 77, 3, 23, 92, 37, 42, 252, 113, 30, 1, 2, 96, 135, 145, 153, 154, 42, 169, 114, 
89, 14, 154, 199, 204, 132, 76, 223, 185, 243, 236, 137, 36, 117, 60, 219, 53, 198, 215, 254, 254, 155, 100, 67, 75, 214, 6, 95, 23, 172, 14, 2, 
234, 70, 69, 149, 176, 213, 185, 123, 52, 189, 119, 116, 242, 189, 27, 152, 98, 187, 155, 145, 92, 38, 57, 108, 204, 131, 252, 191, 88, 43, 167, 125, 
16, 178, 128, 37, 242, 36, 230, 176, 77, 108, 17, 246, 174, 39, 223, 209, 148, 48, 45, 208, 121, 39, 128, 186, 103, 71, 145, 173, 192, 184, 121, 31, 
93, 212, 8, 131, 169, 108, 26, 242, 234, 140, 88, 120, 95, 215, 80, 116, 69, 250, 75, 188, 144, 49, 194, 214, 101, 127, 226, 7, 253, 146, 12, 135, 
49, 214, 159, 167, 50, 214, 31, 28, 189, 80, 239, 72, 85, 35, 186, 212, 180, 153, 190, 64, 36, 0, 15, 205, 217, 53, 29, 141, 3, 29, 115, 191, 
174, 138, 18, 111, 51, 177, 74, 111, 59, 147, 135, 160, 40, 128, 245, 177, 235, 48, 85, 45, 253, 116, 254, 24, 159, 24, 111, 237, 12, 228, 73, 57, 
196, 104, 51, 160, 154, 115, 118, 152, 161, 217, 211, 159, 183, 144, 95, 46, 188, 141, 230, 61, 48, 154, 178, 149, 89, 126, 20, 188, 156, 158, 176, 205, 
38, 146, 221, 232, 156, 185, 11, 170, 249, 80, 145, 77, 44, 27, 221, 217, 189, 39, 83, 20, 19, 163, 209, 138, 114, 104, 76, 118, 127, 38, 82, 188, 
80, 210, 244, 222, 184, 76, 240, 32, 16, 200, 133, 155, 243, 18, 223, 166, 82, 26, 128, 57, 74, 234, 140, 169, 29, 125, 96, 126, 202, 129, 97, 175, 
135, 154, 100, 1, 180, 25, 158, 220, 125, 190, 126, 96, 200, 140, 91, 243, 160, 45, 95, 33, 189, 242, 156, 7, 84, 14, 162, 33, 216, 220, 152, 184, 
217, 3, 32, 180, 157, 55, 16, 43, 159, 86, 81, 93, 168, 204, 205, 134, 155, 203, 229, 36, 160, 102, 64, 34, 218, 16, 109, 146, 77, 139, 57, 79, 
28, 206, 34, 72, 200, 228, 201, 189, 156, 92, 218, 58, 220, 58, 63, 138, 251, 13, 20, 133, 108, 24, 65, 227, 59, 37, 31, 237, 20, 12, 14, 85, 
233, 101, 110, 241, 213, 136, 214, 176, 101, 66, 1, 134, 243, 101, 61, 149, 65, 174, 241, 111, 227, 1, 239, 153, 200, 147, 36, 56, 97, 1, 106, 20, 
168, 218, 16, 206, 168, 176, 204, 135, 174, 36, 175, 185, 198, 7, 221, 164, 180, 21, 140, 241, 14, 70, 37, 250, 158, 74, 235, 93, 177, 55, 39, 61, 
132, 230, 27, 230, 112, 20, 199, 43, 248, 197, 221, 53, 116, 0, 191, 29, 103, 79, 253, 9, 64, 48, 63, 39, 158, 225, 239, 49, 198, 164, 167, 231, 
116, 234, 169, 38, 162, 145, 107, 240, 137, 147, 136, 65, 101, 89, 9, 202, 50, 17, 99, 150, 18, 50, 39, 164, 115, 154, 177, 112, 174, 101, 213, 151, 
50, 242, 223, 99, 251, 47, 228, 146, 112, 159, 180, 12, 72, 66, 103, 228, 181, 185, 228, 100, 101, 230, 78, 98, 145, 90, 187, 190, 187, 188, 35, 51, 
69, 173, 232, 93, 132, 27, 231, 51, 132, 166, 111, 175, 23, 20, 19, 7, 90, 78, 177, 36, 100, 17, 172, 184, 50, 176, 157, 166, 138, 25, 139, 12, 
248, 118, 247, 185, 135, 173, 176, 94, 99, 12, 206, 43, 15, 79, 200, 54, 82, 123, 2, 112, 129, 154, 193, 102, 89, 214, 240, 158, 254, 13, 143, 220, 
98, 78, 72, 6, 156, 99, 4, 7, 116, 218, 238, 102, 185, 155, 206, 223, 148, 151, 20, 202, 117, 150, 150, 145, 208, 171, 87, 2, 68, 87, 59, 196, 
94, 221, 29, 185, 160, 227, 46, 136, 230, 198, 246, 50, 229, 203, 243, 216, 227, 160, 47, 157, 67, 63, 186, 200, 43, 182, 122, 20, 205, 218, 31, 78, 
146, 120, 194, 48, 185, 253, 3, 165, 176, 44, 18, 70, 172, 213, 141, 94, 198, 59, 162, 59, 52, 247, 71, 5, 196, 38, 11, 2, 88, 164, 87, 105, 
106, 23, 139, 178, 86, 167, 223, 136, 145, 13, 118, 66, 108, 220, 124, 22, 144, 180, 198, 220, 216, 74, 220, 164, 190, 211, 195, 222, 231, 232, 133, 112, 
27, 90, 209, 109, 43, 0, 167, 197, 16, 22, 98, 174, 205, 39, 36, 12, 88, 4, 249, 165, 13, 233, 162, 110, 5, 61, 99, 166, 199, 5, 210, 35, 
161, 140, 250, 118, 54, 76, 199, 87, 122, 155, 26, 251, 192, 38, 116, 181, 254, 197, 163, 158, 241, 175, 73, 144, 74, 139, 181, 62, 139, 125, 242, 170, 
195, 158, 113, 203, 190, 252, 52, 160, 232, 150, 234, 128, 124, 114, 226, 239, 46, 64, 51, 186, 239, 159, 10, 163, 8, 141, 138, 113, 15, 253, 32, 153, 
12, 44, 168, 84, 80, 166, 104, 109, 56, 173, 42, 126, 129, 204, 110, 1, 86, 95, 32, 210, 186, 227, 164, 165, 131, 187, 187, 244, 118, 92, 28, 230, 
209, 115, 27, 221, 194, 9, 106, 238, 17, 42, 53, 29, 150, 30, 157, 147, 176, 186, 233, 170, 76, 206, 96, 254, 196, 52, 43, 99, 46, 148, 49, 244, 
48, 97, 77, 30, 50, 11, 196, 194, 224, 0, 114, 108, 204, 117, 126, 191, 60, 142, 23, 235, 227, 218, 15, 125, 161, 190, 192, 65, 232, 201, 50, 140, 
13, 133, 201, 179, 6, 186, 141, 233, 223, 203, 77, 100, 122, 13, 166, 0, 195, 192, 56, 39, 14, 171, 8, 88, 177, 203, 111, 250, 162, 75, 121, 222, 
20, 25, 36, 36, 234, 78, 95, 207, 11, 207, 61, 228, 65, 68, 53, 58, 215, 223, 226, 215, 155, 10, 44, 46, 90, 114, 47, 228, 158, 139, 232
};

PROGMEM const wavetable_t WAVE_LINEAR = {
0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 
8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 
16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 
24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31, 32, 
32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 40, 
40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 
48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 
56, 56, 56, 57, 57, 57, 57, 58, 58, 58, 58, 59, 59, 59, 59, 60, 60, 60, 60, 61, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63, 63, 64, 
64, 64, 64, 65, 65, 65, 65, 66, 66, 66, 66, 67, 67, 67, 67, 68, 68, 68, 68, 69, 69, 69, 69, 70, 70, 70, 70, 71, 71, 71, 71, 72, 
72, 72, 72, 73, 73, 73, 73, 74, 74, 74, 74, 75, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 78, 78, 78, 78, 79, 79, 79, 79, 80, 
80, 80, 80, 81, 81, 81, 81, 82, 82, 82, 82, 83, 83, 83, 83, 84, 84, 84, 84, 85, 85, 85, 85, 86, 86, 86, 86, 87, 87, 87, 87, 88, 
88, 88, 88, 89, 89, 89, 89, 90, 90, 90, 90, 91, 91, 91, 91, 92, 92, 92, 92, 93, 93, 93, 93, 94, 94, 94, 94, 95, 95, 95, 95, 96, 
96, 96, 96, 97, 97, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 100, 100, 100, 100, 101, 101, 101, 101, 102, 102, 102, 102, 103, 103, 103, 103, 104, 
104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 107, 107, 107, 107, 108, 108, 108, 108, 109, 109, 109, 109, 110, 110, 110, 110, 111, 111, 111, 111, 112, 
112, 112, 112, 113, 113, 113, 113, 114, 114, 114, 114, 115, 115, 115, 115, 116, 116, 116, 116, 117, 117, 117, 117, 118, 118, 118, 118, 119, 119, 119, 119, 120, 
120, 120, 120, 121, 121, 121, 121, 122, 122, 122, 122, 123, 123, 123, 123, 124, 124, 124, 124, 125, 125, 125, 125, 126, 126, 126, 126, 127, 127, 127, 127, 128, 
128, 128, 128, 129, 129, 129, 129, 130, 130, 130, 130, 131, 131, 131, 131, 132, 132, 132, 132, 133, 133, 133, 133, 134, 134, 134, 134, 135, 135, 135, 135, 136, 
136, 136, 136, 137, 137, 137, 137, 138, 138, 138, 138, 139, 139, 139, 139, 140, 140, 140, 140, 141, 141, 141, 141, 142, 142, 142, 142, 143, 143, 143, 143, 144, 
144, 144, 144, 145, 145, 145, 145, 146, 146, 146, 146, 147, 147, 147, 147, 148, 148, 148, 148, 149, 149, 149, 149, 150, 150, 150, 150, 151, 151, 151, 151, 152, 
152, 152, 152, 153, 153, 153, 153, 154, 154, 154, 154, 155, 155, 155, 155, 156, 156, 156, 156, 157, 157, 157, 157, 158, 158, 158, 158, 159, 159, 159, 159, 160, 
160, 160, 160, 161, 161, 161, 161, 162, 162, 162, 162, 163, 163, 163, 163, 164, 164, 164, 164, 165, 165, 165, 165, 166, 166, 166, 166, 167, 167, 167, 167, 168, 
168, 168, 168, 169, 169, 169, 169, 170, 170, 170, 170, 171, 171, 171, 171, 172, 172, 172, 172, 173, 173, 173, 173, 174, 174, 174, 174, 175, 175, 175, 175, 176, 
176, 176, 176, 177, 177, 177, 177, 178, 178, 178, 178, 179, 179, 179, 179, 180, 180, 180, 180, 181, 181, 181, 181, 182, 182, 182, 182, 183, 183, 183, 183, 184, 
184, 184, 184, 185, 185, 185, 185, 186, 186, 186, 186, 187, 187, 187, 187, 188, 188, 188, 188, 189, 189, 189, 189, 190, 190, 190, 190, 191, 191, 191, 191, 192, 
192, 192, 192, 193, 193, 193, 193, 194, 194, 194, 194, 195, 195, 195, 195, 196, 196, 196, 196, 197, 197, 197, 197, 198, 198, 198, 198, 199, 199, 199, 199, 200, 
200, 200, 200, 201, 201, 201, 201, 202, 202, 202, 202, 203, 203, 203, 203, 204, 204, 204, 204, 205, 205, 205, 205, 206, 206, 206, 206, 207, 207, 207, 207, 208, 
208, 208, 208, 209, 209, 209, 209, 210, 210, 210, 210, 211, 211, 211, 211, 212, 212, 212, 212, 213, 213, 213, 213, 214, 214, 214, 214, 215, 215, 215, 215, 216, 
216, 216, 216, 217, 217, 217, 217, 218, 218, 218, 218, 219, 219, 219, 219, 220, 220, 220, 220, 221, 221, 221, 221, 222, 222, 222, 222, 223, 223, 223, 223, 224, 
224, 224, 224, 225, 225, 225, 225, 226, 226, 226, 226, 227, 227, 227, 227, 228, 228, 228, 228, 229, 229, 229, 229, 230, 230, 230, 230, 231, 231, 231, 231, 232, 
232, 232, 232, 233, 233, 233, 233, 234, 234, 234, 234, 235, 235, 235, 235, 236, 236, 236, 236, 237, 237, 237, 237, 238, 238, 238, 238, 239, 239, 239, 239, 240, 
240, 240, 240, 241, 241, 241, 241, 242, 242, 242, 242, 243, 243, 243, 243, 244, 244, 244, 244, 245, 245, 245, 245, 246, 246, 246, 246, 247, 247, 247, 247, 248, 
248, 248, 248, 249, 249, 249, 249, 250, 250, 250, 250, 251, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 254, 254, 254, 254, 255, 255, 255, 255
};

// exponential correction curve for the human eye
// formula: (int)(pow(2.0, 8.0 * (i + 1) / 256)) - 1; i = 0..255
PROGMEM const uint8_t eye_correction[256] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 
7, 7, 7, 7, 8, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 15, 15, 
15, 16, 16, 16, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28, 29, 30, 31, 31, 
32, 33, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 55, 56, 57, 58, 60, 61, 63, 64, 
65, 67, 68, 70, 71, 73, 75, 76, 78, 80, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 102, 104, 106, 108, 111, 113, 116, 118, 121, 124, 127, 129, 
132, 135, 138, 141, 144, 147, 151, 154, 157, 161, 164, 168, 172, 176, 180, 183, 188, 192, 196, 200, 205, 209, 214, 218, 223, 228, 233, 238, 244, 249, 255  
};

/*******************************************************
* PWM Control
*******************************************************/

inline void setPinValue(uint8_t pin, timermap_t* timermap, uint8_t val) {
  if (pin == 0)
    return;

  // set PWM value, do not use analogWrite for performance
  *(volatile char*)(timermap->timerReg) |= _BV(timermap->outputMode);
  // special treatment for halogen pin (invert)
  *(volatile char*)(timermap->ocrReg) = (pin == outputPins[0] ? 255 - val : val);
}

inline void setChannelValues(channel_t* channel, uint8_t val) {
  // apply value to the controlled pins
  // special case: first pin (halogen lamp) is controlled by
  // any channel that has its bitmask value set to 0
  if (channel->bitmask == 0) {
    setPinValue(outputPins[0], &(timerMaps[0]), val);
  } else {
    uint8_t b = 1;    // the lowest bit corresponds to the first LED
    uint8_t mask = channel->bitmask;
    while (mask > 0) {
      // test bit if the pin is defined
      if ((mask & 1) == 1 && outputPins[b] > 0) {
        // bit is set, i. e. LED no. b is controlled by this channel
        // special treatment for pin 4 (won't turn off completely on Mega)
        if (outputPins[b] == 4)
          analogWrite(outputPins[b], val);
        else {
          // set PWM value, do not use analogWrite for performance
          setPinValue(outputPins[b], &(timerMaps[b]), val);
        }
      }
      mask >>= 1;
      b++;
    }
  }
}

ISR(PWM_TIMER_VECTOR)        // interrupt service routine 
{
  PWM_TIMER_COUNTER = PWM_TIMER_PRELOAD;   // preload timer

  // disable all LEDs when the speed is 0
  if (global_speed == 0) {
    for (int i = 0; i < LUCINDA_MAXCHANNELS; i++)
      setChannelValues(&(channels[i]), 0);
    return;
  }

  // regular running mode
  // go through all channels
  for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
    uint8_t val = 0;
    if (channels[i].enabled == 1 && channels[i].period > 0) {
      uint8_t val = channels[i].brightness;  // assume square
      // calculate end of cycle if the duty cycle is > 0
      if (channels[i].dutycycle > 0) {
        // calculate length of in-phase cycle
        int16_t phaseLength = ((uint32_t)channels[i].period * (channels[i].dutycycle + 1)) / 256;
        // apply phaseshift
        // phaseshift is guaranteed to be less or equal than the period
        int16_t phaseEnd = (channels[i].phaseshift + phaseLength) % (channels[i].period + 1);
        // correct for wrapover
        int16_t phaseStart = channels[i].phaseshift > phaseEnd ? (phaseEnd - phaseLength) : channels[i].phaseshift;
        // "on" phase?
        bool onPhase = ((int16_t)channels[i].counter >= phaseStart) && (channels[i].counter < phaseEnd);
        if (onPhase) {
          // "on" phase
          // non-square wave?
          if (channels[i].wavetable != nullptr) {
            // calculate the index in the wavetable
            uint16_t index = (int32_t)(channels[i].counter - phaseStart) * (WAVETABLE_SIZE - 1) / phaseLength;
            // reverse?
            if ((channels[i].flags & CHANNELFLAG_REVERSE) == CHANNELFLAG_REVERSE)
              index = (WAVETABLE_SIZE - 1) - index;
            val = pgm_read_byte((uint32_t)channels[i].wavetable + index);
          }
          // adjust brightness
          if (channels[i].brightness < 255) {
            val = ((uint16_t)val * channels[i].brightness) / 256;
          }
          // apply offset
          if (val < channels[i].offset)
            val = channels[i].offset;
        } else {
          // "off" phase
          val = channels[i].offset;
        }
      } else {
        // duty cycle is 0, always at base level
        val = channels[i].offset;
      }

      // inversion?
      if ((channels[i].flags & CHANNELFLAG_INVERT) == CHANNELFLAG_INVERT)
        val = 255 - val;

      // apply global brightness
      if (global_brightness < 255) {
        val = ((uint16_t)val * global_brightness) / 256;
      }
      
      // apply eye correction?
      if ((channels[i].flags & CHANNELFLAG_NO_EYE_CORRECTION) == 0)
        val = pgm_read_byte((uint32_t)&eye_correction + val);
      
      // set value to all controlled outputs
      setChannelValues(&(channels[i]), val);
  
      channels[i].counter += global_speed;
      if (channels[i].counter > channels[i].period)
        channels[i].counter = 0;
    }
  }  // for (channels)
}

/*******************************************************
* Arducom commands
*******************************************************/
#define ARDUCOM_COMMAND_GETCONFIG 1
#define ARDUCOM_COMMAND_DEFINECHANNEL 2
#define ARDUCOM_COMMAND_SETSPEED 3

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
// byte 0: channel number (may be 0 to LUCINDA_MAXCHANNELS - 1)
// byte 1: enabled flag. The channel is used if the flag is 1.
// byte 2: bit mask for the outputs. Each bit corresponds to an LED. If no bit is set the channel is for the halogen lamp.
// bytes 3 and 4: period (LSB first)
// byte 5: offset
// byte 6: brightness factor
// byte 7: duty cycle
// bytes 8 and 9: phase shift (LSB first)
// byte 10: wavetable to use (0: square, 1: sine, 2: triangle, 3: flicker, 4: linear/sawtooth)
// byte 11: flags that control additional behavior
// The channel is disabled and all pins are set to 0.
// After all values have been applied the channel is switched on again.
// If an error occurs the channel remains switched off.
class ArducomDefineChannel: public ArducomCommand {
public:
  ArducomDefineChannel(uint8_t commandCode) : ArducomCommand(commandCode, 12) {}   // number of expected parameter bytes
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    uint8_t channelNo = dataBuffer[0];
    if (channelNo > (LUCINDA_MAXCHANNELS) - 1) {
      *errorInfo = LUCINDA_MAXCHANNELS - 1;
      return ARDUCOM_LIMIT_EXCEEDED;
    }
    // disable channel during aplication
    channels[channelNo].enabled = 0;
    // reset counter
    channels[channelNo].counter = 0;
    // switch off all LEDs
    setChannelValues(&(channels[channelNo]), 0);
    channels[channelNo].bitmask = dataBuffer[2];
    channels[channelNo].period = dataBuffer[3] + dataBuffer[4] * 256;
    if (channels[channelNo].period > WAVETABLE_SIZE * 10) {
      *errorInfo = 3;
      return ARDUCOM_FUNCTION_ERROR;
    }
    channels[channelNo].offset = dataBuffer[5];
    channels[channelNo].brightness = dataBuffer[6];
    channels[channelNo].dutycycle = dataBuffer[7];
    channels[channelNo].phaseshift = (dataBuffer[8] + dataBuffer[9] * 256) % channels[channelNo].period;
    uint8_t wavetable = dataBuffer[10];
    switch (wavetable) {
      case 0: // square
        channels[channelNo].wavetable = nullptr;
        break;
      case 1: // sine
        channels[channelNo].wavetable = &WAVE_SINE;
        break;
      case 2: // triangle
        channels[channelNo].wavetable = &WAVE_TRIANGLE;
        break;
      case 3: // flicker
        channels[channelNo].wavetable = &WAVE_FLICKER;
        break;
      case 4: // linear (sawtooth)
        channels[channelNo].wavetable = &WAVE_LINEAR;
        break;
      default:  {
        *errorInfo = 10;
        return ARDUCOM_FUNCTION_ERROR;
      }
    }
    channels[channelNo].flags = dataBuffer[11] & CHANNELFLAG_ALL;
    channels[channelNo].enabled = dataBuffer[1] & 0x01; // the lowest bit decides
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};

// This command sets the global speed of the channels in ticks. One tick corresponds to one millisecond.
class ArducomSetSpeed: public ArducomCommand {
public:
  ArducomSetSpeed(uint8_t commandCode) : ArducomCommand(commandCode, 1) {}   // this command expects one parameter
  
  int8_t handle(Arducom* arducom, uint8_t* dataBuffer, int8_t* dataSize, uint8_t* destBuffer, const uint8_t maxBufferSize, uint8_t* errorInfo) {
    global_speed = dataBuffer[0];
    *dataSize = 0;
    return ARDUCOM_OK;
  }
};


/*******************************************************
* Arducom system variables
*******************************************************/

ArducomTransportStream arducomTransport(&Serial);
Arducom arducom(&arducomTransport);

/*******************************************************
* Setup
*******************************************************/

void addCommand(ArducomCommand* cmd) {
  uint8_t code = arducom.addCommand(cmd);
  if (code != ARDUCOM_OK) {
    Serial.print(F("Setup error: Error adding command "));
    Serial.print((int)cmd->commandCode);
    Serial.print(F(" (code "));
    Serial.print(code);
    Serial.println(F(")"));
    while (true);
  }
}

void fillTimerMaps() {
  for (int i = 0; i < LUCINDA_MAXCHANNELS; i++) {
    if (outputPins[i] == 0)
      continue;
    if (!fillTimerMap(&(timerMaps[i]), outputPins[i])) {
      Serial.print(F("Setup error: Pin not on timer: "));
      Serial.println(outputPins[i]);
      while (true);
    }
  }
/*  
  Serial.print("timerMaps[0] = {");
  Serial.print(timerMaps[0].timerReg);
  Serial.print(", ");
  Serial.print(timerMaps[0].outputMode);
  Serial.print(", ");
  Serial.print(timerMaps[0].ocrReg);
  Serial.println(")");
*/  
}

void setup()
{	
  // setup pins
  // special treatment for halogen pin
  pinMode(outputPins[0], OUTPUT);
  analogWrite(outputPins[0], 255);
  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++)
    if (outputPins[i] != 0) {
      pinMode(outputPins[i], OUTPUT);
      analogWrite(outputPins[i], 0);
    }
  
	// initialize hardware
	Serial.begin(57600);

#ifdef LUCINDA_DEBUG
  Serial.println(F(APP_NAME));
#endif

  fillTimerMaps();

  uint8_t code;
	// setup Arducom system
  addCommand(new ArducomVersionCommand(APP_NAME));
  addCommand(new ArducomGetConfig(ARDUCOM_COMMAND_GETCONFIG));
  addCommand(new ArducomDefineChannel(ARDUCOM_COMMAND_DEFINECHANNEL));
  addCommand(new ArducomSetSpeed(ARDUCOM_COMMAND_SETSPEED));

#ifdef LUCINDA_DEBUG
  Serial.println(F("Setup complete."));
#endif

  // test: initialize channel 0
  channels[0].period = WAVETABLE_SIZE;
  channels[0].enabled = 0;
  channels[0].dutycycle = 127;

  for (int i = 1; i < LUCINDA_MAXCHANNELS; i++) {
    channels[i].period = WAVETABLE_SIZE * 2;
    channels[i].bitmask = 1 << (i - 1);
    channels[i].enabled = 1;
    channels[i].brightness = 255;
    channels[i].dutycycle = 127;
    channels[i].phaseshift = i * WAVETABLE_SIZE / LUCINDA_MAXCHANNELS;
    channels[i].wavetable = &WAVE_SINE;
  } 

/*
    // debug
  channels[8].period = 0x800;
  channels[8].phaseshift = 0x500;
  channels[8].dutycycle = 0x2F;
  int i = 8;
  for (channels[8].counter = 0; channels[8].counter < channels[8].period; channels[8].counter += 10) {
      uint8_t val = channels[i].brightness;  // assume square
        // calculate length of in-phase cycle
        int16_t phaseLength = ((uint32_t)channels[i].period * (channels[i].dutycycle + 1)) / 256;
        Serial.print("phaseLength: " );
        Serial.println(phaseLength);
        // apply phaseshift
        // phaseshift is guaranteed to be less or equal than the period
        int16_t phaseEnd = (channels[i].phaseshift + phaseLength) % (channels[i].period + 1);
        Serial.print("phaseEnd: " );
        Serial.println(phaseEnd);
        // correct for wrapover
        int16_t phaseStart = channels[i].phaseshift > phaseEnd ? (phaseEnd - phaseLength) : channels[i].phaseshift;
        Serial.print("phaseStart: " );
        Serial.println(phaseStart);
        // "on" phase?
          Serial.print("counter: " );
          Serial.println(channels[i].counter);
        if ((((int16_t)channels[i].counter >= phaseStart) && (channels[i].counter < phaseEnd))) {
          // "on" phase
          // adjust brightness
          if (channels[i].brightness < 255) {
            val = ((uint16_t)val * channels[i].brightness) / 256;
          }
          // apply offset
          if (val < channels[i].offset)
            val = channels[i].offset;
        } else {
          // "off" phase
          val = channels[i].offset;
        }
        Serial.print("val: " );
        Serial.println(val);
  }
 */ 
/*  
  channels[2].period = WAVETABLE_SIZE * 2;
  channels[2].bitmask = 4;
  channels[2].enabled = 1;
  channels[2].brightness = 255;
  channels[2].dutycycle = 127;
  channels[2].phaseshift = WAVETABLE_SIZE;
*/
  noInterrupts();
  
  PWM_TIMER_INIT

  interrupts();
}

/*******************************************************
* Main loop
*******************************************************/

void loop()
{
	// handle Arducom commands
	arducom.doWork();
}
