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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalcomponent for testing
    icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    
    // Test icalcomponent_add_component
    icalcomponent_add_component(parent, child);

    // Test icalcomponent_get_parent
    icalcomponent *retrievedParent = icalcomponent_get_parent(child);
    if (retrievedParent != parent) {
        std::cerr << "Error: Parent not correctly set" << std::endl;
    }

    // Test icalcomponent_remove_component
    icalcomponent_remove_component(parent, child);

    // Create a dummy icalproperty for testing
    icalproperty *property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    icalcomponent_add_property(child, property);

    // Test icalproperty_get_parent
    icalcomponent *propertyParent = icalproperty_get_parent(property);
    if (propertyParent != child) {
        std::cerr << "Error: Property parent not correctly set" << std::endl;
    }

    // Test icalcomponent_set_parent
    icalcomponent_set_parent(child, parent);
    if (icalcomponent_get_parent(child) != parent) {
        std::cerr << "Error: Parent not correctly set after set_parent" << std::endl;
    }

    // Cleanup: remove property and free it
    icalcomponent_remove_property(child, property);
    icalproperty_free(property);

    // Test icalcomponent_free
    icalcomponent_remove_component(parent, child);
    icalcomponent_free(child);
    icalcomponent_free(parent);

    return 0;
}