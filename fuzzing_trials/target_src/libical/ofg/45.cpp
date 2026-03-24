#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

extern "C" {
#include <libical/ical.h>

void sample_callback(icalparameter *param, void *data) {
    // Sample callback function for demonstration purposes
}

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) return 0;

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_foreach_tzid(component, sample_callback, NULL);

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the buffer
    free(buffer);

    return 0;
}

}