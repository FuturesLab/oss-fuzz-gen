// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_count_errors at icalcomponent.c:1123:5 in icalcomponent.h
// icalcomponent_count_components at icalcomponent.c:583:5 in icalcomponent.h
// icalcomponent_clone at icalcomponent.c:129:16 in icalcomponent.h
// icalcomponent_is_valid at icalcomponent.c:295:6 in icalcomponent.h
// icalcomponent_new_xstandard at icalcomponent.c:2060:16 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
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
#include <fstream>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a new VEVENT component
    icalcomponent *vevent = icalcomponent_new_vevent();
    if (!vevent) {
        return 0;
    }

    // Create a new XSTANDARD component
    icalcomponent *xstandard = icalcomponent_new_xstandard();
    if (!xstandard) {
        icalcomponent_free(vevent);
        return 0;
    }

    // Check if VEVENT is valid
    bool is_vevent_valid = icalcomponent_is_valid(vevent);

    // Check if XSTANDARD is valid
    bool is_xstandard_valid = icalcomponent_is_valid(xstandard);

    // Clone VEVENT component
    icalcomponent *cloned_vevent = icalcomponent_clone(vevent);
    if (cloned_vevent) {
        icalcomponent_free(cloned_vevent);
    }

    // Count errors in VEVENT
    int vevent_errors = icalcomponent_count_errors(vevent);

    // Count errors in XSTANDARD
    int xstandard_errors = icalcomponent_count_errors(xstandard);

    // Count components in VEVENT of kind VEVENT
    int vevent_count = icalcomponent_count_components(vevent, ICAL_VEVENT_COMPONENT);

    // Count components in XSTANDARD of kind XSTANDARD
    int xstandard_count = icalcomponent_count_components(xstandard, ICAL_XSTANDARD_COMPONENT);

    // Cleanup
    icalcomponent_free(vevent);
    icalcomponent_free(xstandard);

    return 0;
}