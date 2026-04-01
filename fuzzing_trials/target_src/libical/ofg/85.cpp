#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalcomponent
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

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);
    if (component != NULL) {
        // Call the function-under-test
        icalproperty_method method = icalcomponent_get_method(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(buffer);

    return 0;
}