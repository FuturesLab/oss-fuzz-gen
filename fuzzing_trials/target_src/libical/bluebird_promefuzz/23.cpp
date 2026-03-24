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
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
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