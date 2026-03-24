#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < 2) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the icalproperty_kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Create a new property with the determined kind
    icalproperty *property = icalproperty_new(kind);
    if (property != NULL) {
        // Add the property to the component
        icalcomponent_add_property(component, property);
    }

    // Call the function-under-test
    icalcomponent_remove_property_by_kind(component, kind);

    // Clean up
    icalcomponent_free(component);

    return 0;
}