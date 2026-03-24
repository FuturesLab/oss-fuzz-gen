#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "libical/ical.h"
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>

static void tzid_callback(icalparameter *param, void *data) {
    // Placeholder callback function for icalcomponent_foreach_tzid
    (void)param;
    (void)data;
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
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