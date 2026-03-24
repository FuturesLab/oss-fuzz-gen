#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Create an icalcomponent to act as a parent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (parent_component == NULL) {
        icalproperty_free(property);
        return 0;
    }

    // Add the property to the parent component
    icalcomponent_add_property(parent_component, property);

    // Call the function-under-test
    icalcomponent *parent = icalproperty_get_parent(property);

    // Clean up
    icalcomponent_remove_property(parent_component, property);
    icalproperty_free(property);
    icalcomponent_free(parent_component);

    return 0;
}