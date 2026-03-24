#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Create a temporary buffer to hold the input data
    char *temp_data = (char *)malloc(size + 1);
    if (temp_data == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data into the temporary buffer and null-terminate it
    memcpy(temp_data, data, size);
    temp_data[size] = '\0';

    // Parse the input data to create an icalcomponent
    icalcomponent *component = icalparser_parse_string(temp_data);

    // Ensure the component is not NULL before calling the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        struct icaltime_span span = icalcomponent_get_span(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(temp_data);

    return 0;
}