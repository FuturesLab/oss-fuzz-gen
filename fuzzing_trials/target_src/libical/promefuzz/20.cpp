// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_foreach_tzid at icalcomponent.c:2393:6 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_get_inner at icalcomponent.c:1490:16 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "ical.h"
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>

static void tzid_callback(icalparameter *param, void *data) {
    // Placeholder callback function for icalcomponent_foreach_tzid
    (void)param;
    (void)data;
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VCALENDAR component
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    if (!vcalendar) return 0;

    // Create a new VEVENT component
    icalcomponent *vevent = icalcomponent_new_vevent();
    if (!vevent) {
        icalcomponent_free(vcalendar);
        return 0;
    }

    // Add VEVENT to VCALENDAR
    icalcomponent_add_component(vcalendar, vevent);

    // Create a new VRESOURCE component
    icalcomponent *vresource = icalcomponent_new_vresource();
    if (!vresource) {
        icalcomponent_free(vcalendar);
        return 0;
    }

    // Add VRESOURCE to VCALENDAR
    icalcomponent_add_component(vcalendar, vresource);

    // Retrieve the inner component
    icalcomponent *inner = icalcomponent_get_inner(vcalendar);
    if (inner) {
        // Iterate over TZID parameters in the inner component
        icalcomponent_foreach_tzid(inner, tzid_callback, nullptr);
    }

    // Cleanup
    icalcomponent_free(vcalendar);

    return 0;
}