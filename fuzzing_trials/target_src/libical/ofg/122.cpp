#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Corrected include path for libical

    // Function under test
    const char *icalcomponent_get_location(icalcomponent *);
    void icalcomponent_set_location(icalcomponent *, const char *);
}

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to perform meaningful operations
    if (size < 1) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Create a temporary string to use as location
    char location[256];
    size_t copy_size = size < sizeof(location) - 1 ? size : sizeof(location) - 1;
    memcpy(location, data, copy_size);
    location[copy_size] = '\0';

    // Set the location of the component
    icalcomponent_set_location(component, location);

    // Call the function under test
    const char *result = icalcomponent_get_location(component);

    // Clean up
    icalcomponent_free(component);

    return 0;
}