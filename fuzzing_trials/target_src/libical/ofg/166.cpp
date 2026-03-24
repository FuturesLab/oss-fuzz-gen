#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Ensure there's enough data to perform meaningful operations
    if (size < 2) {
        return 0;
    }

    // Initialize a memory context or any necessary setup if required
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0; // Exit if component creation fails
    }

    // Create a property to add and later remove
    icalproperty *property = icalproperty_new_summary("Test Summary");
    if (property == NULL) {
        icalcomponent_free(component);
        return 0; // Exit if property creation fails
    }

    // Add the property to the component
    icalcomponent_add_property(component, property);

    // Fuzzing logic: Attempt to remove the property using the function-under-test
    icalcomponent_remove_property(component, property);

    // Cleanup
    icalcomponent_free(component);

    return 0;
}