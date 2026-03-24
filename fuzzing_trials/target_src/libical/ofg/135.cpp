#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    // Ensure the data is null-terminated for safe string operations
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Create an icalcomponent from the string data
    icalcomponent *component = icalparser_parse_string(data_copy);

    // Call the function-under-test if the component is successfully created
    if (component != NULL) {
        const char *comment = icalcomponent_get_comment(component);
        // Use the comment in some way to avoid compiler optimizations removing it
        if (comment != NULL) {
            // For fuzzing purposes, we don't need to do anything with the comment
        }
        // Free the component after use
        icalcomponent_free(component);
    }

    // Clean up
    free(data_copy);

    return 0;
}