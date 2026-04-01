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
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
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