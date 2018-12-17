#ifndef GLOBALDEFINES_H_INCLUDED
#define GLOBALDEFINES_H_INCLUDED

// defines the global application namespace for most classes.
#define APP_NAMESPACE   Lucinda

#define APP_INTERNAL_NAME   "LucindaGUI"
#define APP_NAME            "Lucinda GUI Test"
#define APP_VENDOR          ""
#define APP_VERSION         "0.1"
#define APP_CONFIG_GLOBAL   APP_INTERNAL_NAME "_" APP_VERSION ".txt"
#define APP_CONFIG_LOCAL    APP_INTERNAL_NAME "_" APP_VERSION "_user.txt"

// settings constants
#define APPSETTING_MAINGROUP    "Application"

#define APPKEY_NR_OF_DEVICES     "DeviceCount"
#define APPKEY_DEVICENAME_PREFIX "Device"


#define GLOBAL_SPEED_MAX     255
#define CHANNEL_PERIOD_MAX   10240

enum SliderType {
    SLIDER_UNKNOWN,
    SLIDER_BRIGHTNESS,
    SLIDER_GLOBAL_SPEED,
    SLIDER_PERIOD,
    SLIDER_PHASESHIFT,
    SLIDER_OFFSET,
    SLIDER_DUTYCYCLE
};

#endif // GLOBALDEFINES_H_INCLUDED
