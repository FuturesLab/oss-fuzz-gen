#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // If parsing was successful, call the function-under-test
    if (component != NULL) {
        icalcomponent_convert_errors(component);
        icalcomponent_free(component);
    }

    // Free the allocated buffer
    free(buffer);

    return 0;
}