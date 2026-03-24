#include <iostream>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalcomponent and icalproperty
    icalcomponent* component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty* property = icalproperty_new(ICAL_SUMMARY_PROPERTY);

    // Set the property to the component
    icalcomponent_add_property(component, property);

    // Test icalproperty_get_parent
    icalcomponent* parent = icalproperty_get_parent(property);

    // Test icalproperty_set_parent
    icalproperty_set_parent(property, component);

    // Test icalcomponent_get_next_property
    icalproperty* next_property = icalcomponent_get_next_property(component, ICAL_SUMMARY_PROPERTY);

    // Test icalcomponent_get_current_property
    icalproperty* current_property = icalcomponent_get_current_property(component);

    // Test icalcomponent_get_first_property
    icalproperty* first_property = icalcomponent_get_first_property(component, ICAL_SUMMARY_PROPERTY);

    // Test icalcomponent_remove_property
    icalcomponent_remove_property(component, property);

    // Cleanup
    if (property) {
        icalproperty_free(property);
    }
    if (component) {
        icalcomponent_free(component);
    }

    return 0;
}