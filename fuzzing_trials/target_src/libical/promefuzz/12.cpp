// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
// icalcomponent_new_xdaylight at icalcomponent.c:2065:16 in icalcomponent.h
// icalcomponent_free at icalcomponent.c:172:6 in icalcomponent.h
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create new VTIMEZONE component
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    if (!vtimezone) return 0;

    // Create new VALARM component
    icalcomponent *valarm = icalcomponent_new_valarm();
    if (!valarm) {
        icalcomponent_free(vtimezone);
        return 0;
    }

    // Create new XDAYLIGHT component
    icalcomponent *xdaylight = icalcomponent_new_xdaylight();
    if (!xdaylight) {
        icalcomponent_free(valarm);
        icalcomponent_free(vtimezone);
        return 0;
    }

    // Create a new parent component using icalcomponent_vanew
    icalcomponent *parent = icalcomponent_vanew(ICAL_VCALENDAR_COMPONENT, vtimezone, valarm, xdaylight, NULL);
    if (!parent) {
        icalcomponent_free(xdaylight);
        icalcomponent_free(valarm);
        icalcomponent_free(vtimezone);
        return 0;
    }

    // Remove components from parent
    icalcomponent_remove_component(parent, vtimezone);
    icalcomponent_remove_component(parent, valarm);
    icalcomponent_remove_component(parent, xdaylight);

    // Free components
    icalcomponent_free(vtimezone);
    icalcomponent_free(valarm);
    icalcomponent_free(xdaylight);
    icalcomponent_free(parent);

    return 0;
}