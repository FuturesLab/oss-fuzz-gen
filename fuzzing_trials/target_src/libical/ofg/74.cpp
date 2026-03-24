#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Copy data to a null-terminated string
    char *location = (char *)malloc(size + 1);
    if (location == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(location, data, size);
    location[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_location(component, location);

    // Clean up
    free(location);
    icalcomponent_free(component);

    return 0;
}