#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correctly include the libical headers
}

extern "C" int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into the icalcomponent
    icalcomponent *parsed_component = icalparser_parse_string(buffer);

    // Free the temporary buffer
    free(buffer);

    if (parsed_component != NULL) {
        // Call the function-under-test
        bool result = icalcomponent_check_restrictions(parsed_component);

        // Free the parsed component
        icalcomponent_free(parsed_component);
    }

    // Free the initial component
    icalcomponent_free(component);

    return 0;
}