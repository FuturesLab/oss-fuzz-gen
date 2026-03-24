// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_dtend at icalcomponent.c:1566:21 in icalcomponent.h
// icalcomponent_get_recurrenceid at icalcomponent.c:1859:21 in icalcomponent.h
// icalcomponent_get_dtstamp at icalcomponent.c:1722:21 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcompiter_deref at icalcomponent.c:1425:16 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include "ical.h"

static icalcomponent* create_component_from_data(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return nullptr;
    }
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    return icalcomponent_new(kind);
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    // Create a new VCALENDAR component
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    if (!vcalendar) {
        return 0;
    }

    // Create a new VALARM component
    icalcomponent *valarm = icalcomponent_new_valarm();
    if (!valarm) {
        icalcomponent_free(vcalendar);
        return 0;
    }

    // Add the VALARM to the VCALENDAR
    icalcomponent_add_component(vcalendar, valarm);

    // Create a component from data
    icalcomponent *component = create_component_from_data(Data, Size);
    if (component) {
        // Get DTSTAMP
        icaltimetype dtstamp = icalcomponent_get_dtstamp(component);

        // Get DTEND
        icaltimetype dtend = icalcomponent_get_dtend(component);

        // Get RECURRENCE-ID
        icaltimetype recurrence_id = icalcomponent_get_recurrenceid(component);

        // Free the created component
        icalcomponent_free(component);
    }

    // Initialize an iterator
    icalcompiter iter = icalcomponent_begin_component(vcalendar, ICAL_ANY_COMPONENT);

    // Dereference the iterator
    icalcomponent *iter_component = icalcompiter_deref(&iter);

    // Cleanup
    icalcomponent_free(vcalendar);

    return 0;
}