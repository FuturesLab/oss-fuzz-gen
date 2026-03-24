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
#include <cstdint>
#include <cstring>
#include "libical/ical.h"

static icalproperty* create_icalproperty_from_data(const uint8_t* Data, size_t Size) {
    if (Size < sizeof(icalproperty_kind)) {
        return nullptr;
    }
    icalproperty_kind kind;
    std::memcpy(&kind, Data, sizeof(icalproperty_kind));
    return icalproperty_new(kind);
}

static icalcomponent* create_icalcomponent_from_data(const uint8_t* Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return nullptr;
    }
    icalcomponent_kind kind;
    std::memcpy(&kind, Data, sizeof(icalcomponent_kind));
    return icalcomponent_new(kind);
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    // Prepare icalproperty and icalcomponent objects
    icalproperty* property = create_icalproperty_from_data(Data, Size);
    icalcomponent* component = create_icalcomponent_from_data(Data, Size);

    if (property && component) {
        // Test icalproperty_set_parent
        icalproperty_set_parent(property, component);

        // Test icalproperty_get_parent
        icalcomponent* parent = icalproperty_get_parent(property);

        // Test icalcomponent_get_first_property

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalproperty_get_parent to icalcomponent_add_component
        struct icaldurationtype ret_icalcomponent_get_duration_uxxep = icalcomponent_get_duration(parent);

        icalcomponent_add_component(parent, parent);

        // End mutation: Producer.APPEND_MUTATOR

        icalproperty* first_property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

        // Test icalcomponent_get_next_property
        icalproperty* next_property = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY);

        // Test icalcomponent_get_current_property
        icalproperty* current_property = icalcomponent_get_current_property(component);

        // Test icalcomponent_remove_property
        if (first_property) {
            icalcomponent_remove_property(component, first_property);
            icalproperty_free(first_property);
        }

        // Test cleanup
        icalcomponent_remove_property(component, property);
    }

    // Cleanup
    if (property) {
        icalproperty_free(property);
    }
    if (component) {
        icalcomponent_free(component);
    }

    return 0;
}