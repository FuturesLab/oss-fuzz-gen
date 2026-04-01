#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    // Initialize memory for the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Create a temporary icalproperty to add to the component
    icalproperty *property = icalproperty_new_comment("Sample comment");
    if (property != NULL) {
        icalcomponent_add_property(component, property);
    }

    // Call the function-under-test
    icalcomponent_normalize(component);

    // Clean up
    icalcomponent_free(component);

    return 0;
}