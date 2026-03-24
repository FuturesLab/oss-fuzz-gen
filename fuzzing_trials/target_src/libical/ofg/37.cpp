#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent structure
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure the data is not empty and has a reasonable size
    if (size > 0 && size < 1024) {
        // Create a temporary buffer to hold the data
        char *buffer = (char *)malloc(size + 1);
        if (buffer != NULL) {
            // Copy the data into the buffer and null-terminate it
            memcpy(buffer, data, size);
            buffer[size] = '\0';

            // Set some property of the component using the buffer
            icalcomponent_set_summary(component, buffer);

            // Clean up the buffer
            free(buffer);
        }
    }

    // Call the function-under-test
    char *component_name = icalcomponent_get_component_name_r(component);

    // Clean up the component
    icalcomponent_free(component);

    // Return 0 to indicate successful execution
    return 0;
}