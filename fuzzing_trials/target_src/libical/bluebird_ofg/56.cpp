#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent structure
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!component) {
        return 0; // If component creation fails, return early
    }

    // Initialize the icalcompiter structure correctly
    icalcompiter iterator = icalcomponent_begin_component(component, ICAL_VEVENT_COMPONENT);

    // Call the function-under-test
    bool result = icalcompiter_is_valid(&iterator);

    // Clean up
    icalcomponent_free(component);

    return 0;
}