#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Initialize the library
    icaltimezone *zone = icaltimezone_get_utc_timezone();

    // Allocate memory for icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the data is large enough to be used meaningfully
    if (size > 0) {
        // Create a temporary buffer to store the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            return 0;
        }

        // Copy the data and null-terminate it
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Parse the input data as an iCalendar component
        icalcomponent *parsed_component = icalparser_parse_string(buffer);
        if (parsed_component != NULL) {
            // Detach the parsed component and attach it to our component
            icalcomponent_add_component(component, parsed_component);
        }

        // Free the temporary buffer
        free(buffer);
    }

    // Call the function-under-test
    struct icaltimetype dtend = icalcomponent_get_dtend(component);

    // Clean up
    icalcomponent_free(component);

    return 0;
}