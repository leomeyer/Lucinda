#ifndef DEVICEINFO_H_INCLUDED
#define DEVICEINFO_H_INCLUDED

#include "GlobalDefines.h"

namespace APP_NAMESPACE {

    /** Holds information about a device. */
    struct DeviceInfo {
        wxString address;
        wxString status;
        wxString parameters;
        wxString name;
        wxString info;
        int uptime;
        int freeMem;
        int flags;
        wxString config;

        wxString toString()
        {
            wxString result(name);

            result << "; Uptime: ";
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

            result << "; Free RAM: ";
            result << freeMem;

            result << " bytes; Flags: " << flags << (flags & 1 ? " (debug on)" : " (debug off)");

            return result;
        };

    };

}

#endif // DEVICEINFO_H_INCLUDED
