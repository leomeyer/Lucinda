#ifndef DEVICEINFO_H_INCLUDED
#define DEVICEINFO_H_INCLUDED

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

    enum DeviceStatus {
        DEVICE_INACTIVE,
        DEVICE_NOT_CONNECTED,
        DEVICE_CONNECTING,
        DEVICE_ERROR_CONNECTING,
        DEVICE_READY,
        DEVICE_DISCONNECTING,
        DEVICE_ERROR,
        DEVICE_RECONNECTING,
        DEVICE_TERMINATED
    };

    /** Holds information about a device. */
    class DeviceInfo {
    public:
        wxString address;
        DeviceStatus statusCode;
        wxString status;
        wxString parameters;
        wxString name;
        wxString info;
        int uptime;
        int freeMem;
        int flags;
        wxString config;

        static wxString getStatusText(DeviceStatus status) {
            wxString statusText;
            switch (status) {
            case DEVICE_INACTIVE: statusText << "Inactive" ; break;
            case DEVICE_NOT_CONNECTED: statusText << "Not connected" ; break;
            case DEVICE_CONNECTING:  statusText << "Connecting..." ; break;
            case DEVICE_ERROR_CONNECTING: statusText << "Error connecting" ; break;
            case DEVICE_READY: statusText << "Ready" ; break;
            case DEVICE_DISCONNECTING: statusText << "Disconnecting" ; break;
            case DEVICE_ERROR: statusText << "Error" ; break;
            case DEVICE_RECONNECTING: statusText << "Reconnecting..." ; break;
            case DEVICE_TERMINATED: statusText << "Terminated" ; break;
            }

            return statusText;
        };

        wxString freeMemStr() const {
            wxString result;
            if (freeMem > 0)
                result << freeMem;
            else
                result << "-";
            return result;
        }

        wxString uptimeStr() const
        {
            wxString result;

            if (uptime <= 0)
                result << "-";
            else {
                int s = uptime / 1000;
                int m = s / 60;
                int h = m / 60;
                int d = h / 24;
                s = s % 60;
                m = m % 60;
                h = h % 24;
                if ((d > 0) || (h > 0) || (m > 0)) {
                    if (d > 0)
                        result << d << "d ";
                    if ((d > 0) || (h > 0))
                        result << h << "h ";
                    if ((d > 0) || (h > 0) || (m > 0))
                        result << m << "m ";
                    result << s << "s";
                }
            }
            return result;
        };

    };

}

#endif // DEVICEINFO_H_INCLUDED
