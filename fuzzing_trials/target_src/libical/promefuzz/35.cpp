// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_dtend at icalcomponent.c:1566:21 in icalcomponent.h
// icalcomponent_get_dtstamp at icalcomponent.c:1722:21 in icalcomponent.h
// icalcomponent_get_recurrenceid at icalcomponent.c:1859:21 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
// icalcompiter_deref at icalcomponent.c:1425:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize a VCALENDAR component
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    if (!vcalendar) {
        return 0;
    }

    // Create a VALARM component and add it to the VCALENDAR
    icalcomponent *valarm = icalcomponent_new_valarm();
    if (valarm) {
        icalcomponent_add_component(vcalendar, valarm);
    }

    // Use a portion of the input data to determine the type of component to create
    size_t index = Data[0] % ICAL_NUM_COMPONENT_TYPES;
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(index);
    icalcomponent *component = icalcomponent_new(kind);
    if (component) {
        icalcomponent_add_component(vcalendar, component);
    }

    // Initialize an iterator for the components
    icalcompiter iter;
    iter.kind = ICAL_ANY_COMPONENT;
    iter.iter = nullptr;

    // Dereference the current component using the iterator
    icalcomponent *current_component = icalcompiter_deref(&iter);

    // Retrieve DTSTAMP, DTEND, and RECURRENCE-ID from the current component
    if (current_component) {
        icaltimetype dtstamp = icalcomponent_get_dtstamp(current_component);
        icaltimetype dtend = icalcomponent_get_dtend(current_component);
        icaltimetype recurrence_id = icalcomponent_get_recurrenceid(current_component);

        // Perform some basic checks on the returned icaltimetype structures
        if (dtstamp.year < 0 || dtend.year < 0 || recurrence_id.year < 0) {
            std::cerr << "Invalid year in icaltimetype structure" << std::endl;
        }
    }

    // Clean up the components
    icalcomponent_free(vcalendar);

    return 0;
}