#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent and icalproperty_kind
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty_kind kind = ICAL_ANY_PROPERTY;

    // Ensure the data is not empty and has a reasonable size
    if (size > 0) {
        // Use the first byte of data to determine the kind
        kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

        // Add a property of the same kind to the component
        icalproperty *property = icalproperty_new(kind);
        if (property != NULL) {
            icalcomponent_add_property(component, property);
        }
    }

    // Call the function-under-test
    icalcomponent_remove_property_by_kind(component, kind);

    // Clean up the component
    icalcomponent_free(component);

    return 0;
}