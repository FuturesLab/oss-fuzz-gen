#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Initialize a memory zone for icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize an icalcompiter
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function-under-test
    icalcomponent *next_component = icalcompiter_next(&iter);

    // Clean up
    icalcomponent_free(component);

    return 0;
}