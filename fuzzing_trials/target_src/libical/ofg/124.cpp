#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h> // Include the correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a buffer for the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy data into buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // If parsing was successful, test the component
    if (component != NULL) {
        // Call the function-under-test
        bool is_valid = icalcomponent_is_valid(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the buffer
    free(buffer);

    return 0;
}