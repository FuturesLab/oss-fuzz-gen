// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_free at icalcomponent.c:172:6 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
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
#include <cstdint>
#include <cstdarg>
#include <fstream>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VALARM component
    icalcomponent *valarm = icalcomponent_new_valarm();
    if (!valarm) return 0;

    // Create a parent component of a random kind
    icalcomponent_kind parentKind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *parent = icalcomponent_vanew(parentKind, nullptr);

    if (!parent) {
        icalcomponent_free(valarm);
        return 0;
    }

    // Add the VALARM to the parent
    icalcomponent_add_component(parent, valarm);

    // Try removing the VALARM from the parent
    icalcomponent_remove_component(parent, valarm);

    // Try getting the first component of kind ICAL_VALARM_COMPONENT
    icalcomponent *first = icalcomponent_get_first_component(parent, ICAL_VALARM_COMPONENT);

    // Free components in correct order
    if (first) {
        icalcomponent_remove_component(parent, first);
        icalcomponent_free(first);
    } else {
        // Free the valarm if it wasn't removed and freed
        icalcomponent_free(valarm);
    }
    icalcomponent_free(parent);

    // Create a new component using icalcomponent_vanew with random components
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *newComponent = icalcomponent_vanew(kind, nullptr);

    if (newComponent) {
        icalcomponent_free(newComponent);
    }

    return 0;
}