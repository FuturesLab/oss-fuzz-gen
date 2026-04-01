#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalparser.h>
}

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);
    if (component != NULL) {
        // Call the function-under-test
        bool is_valid = icalcomponent_is_valid(component);

        // Clean up
        icalcomponent_free(component);
    }

    // Free the buffer
    free(buffer);

    return 0;
}