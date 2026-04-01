#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract icaldurationtype from the input data
    struct icaldurationtype duration;
    memcpy(&duration, data, sizeof(struct icaldurationtype));

    // Call the function under test
    icalcomponent_set_duration(component, duration);

    // Clean up
    icalcomponent_free(component);

    return 0;
}