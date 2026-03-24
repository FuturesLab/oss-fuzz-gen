// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_convert_errors at icalcomponent.c:1168:6 in icalcomponent.h
// icalcomponent_new_vvoter at icalcomponent.c:2100:16 in icalcomponent.h
// icalcomponent_strip_errors at icalcomponent.c:1145:6 in icalcomponent.h
// icalcomponent_set_method at icalcomponent.c:1499:6 in icalcomponent.h
// icalcomponent_check_restrictions at icalcomponent.c:1117:6 in icalcomponent.h
// icalcomponent_add_property at icalcomponent.c:385:6 in icalcomponent.h
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
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VVOTER component
    icalcomponent *component = icalcomponent_new_vvoter();
    if (!component) return 0;

    // Randomly decide to set a method
    if (Size > 1) {
        icalproperty_method method = static_cast<icalproperty_method>(Data[0] % (ICAL_METHOD_NONE + 1));
        icalcomponent_set_method(component, method);
    }

    // Randomly add a property
    if (Size > 2) {
        icalproperty *property = icalproperty_new(ICAL_UID_PROPERTY);
        if (property) {
            icalcomponent_add_property(component, property);
        }
    }

    // Check restrictions
    bool restrictions_ok = icalcomponent_check_restrictions(component);

    // Convert errors
    icalcomponent_convert_errors(component);

    // Strip errors
    icalcomponent_strip_errors(component);

    // Cleanup
    icalcomponent_free(component);

    return 0;
}