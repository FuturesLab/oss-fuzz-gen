#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Ensure that the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *temp_data = (char *)malloc(size + 1);
    if (temp_data == NULL) {
        // Memory allocation failed
        return 0;
    }

    // Copy the data into the temporary buffer and null-terminate it
    memcpy(temp_data, data, size);
    temp_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *parent = icalparser_parse_string(temp_data);
    if (parent == NULL) {
        // Parsing failed, free the temporary buffer and return
        free(temp_data);
        return 0;
    }

    // Clean up
    icalcomponent_free(parent);
    free(temp_data);

    return 0;
}