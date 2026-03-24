// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_kind_is_valid at icalcomponent.c:1293:6 in icalcomponent.h
// icalcomponent_isa at icalcomponent.c:304:20 in icalcomponent.h
// icalcomponent_get_next_component at icalcomponent.c:627:16 in icalcomponent.h
// icalcomponent_count_components at icalcomponent.c:583:5 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_new at icalcomponent.c:100:16 in icalcomponent.h
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract a kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0]);

    // Check if the kind is valid
    if (!icalcomponent_kind_is_valid(kind)) {
        return 0;
    }

    // Create a new component
    icalcomponent *component = icalcomponent_new(kind);
    if (!component) {
        return 0;
    }

    // Count components of the same kind
    int count = icalcomponent_count_components(component, kind);

    // Get the first component of the specified kind
    icalcomponent *first_component = icalcomponent_get_first_component(component, kind);

    // Get the next component of the specified kind
    icalcomponent *next_component = icalcomponent_get_next_component(component, kind);

    // Determine the kind of the component
    icalcomponent_kind component_kind = icalcomponent_isa(component);

    // Cleanup
    icalcomponent_free(component);

    return 0;
}