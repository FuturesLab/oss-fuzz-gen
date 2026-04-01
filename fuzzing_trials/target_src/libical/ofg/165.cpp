#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data for basic operations

    // Initialize an icalcomponent and icalproperty
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *prop = icalproperty_new(ICAL_SUMMARY_PROPERTY);

    // Add the property to the component
    icalcomponent_add_property(comp, prop);

    // Call the function-under-test
    icalcomponent_remove_property(comp, prop);

    // Clean up
    icalcomponent_free(comp);

    return 0;
}