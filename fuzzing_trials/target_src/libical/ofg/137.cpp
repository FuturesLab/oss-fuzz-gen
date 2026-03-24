#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for safe string operations
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(input);

    // Perform actions on the component if needed
    if (component != NULL) {
        // Example: Convert the component to a string
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // Normally, you would do something with the string here
            // For fuzzing purposes, we might just ensure it is not NULL
            // Removed the print statement to avoid unnecessary output
        }

        // Free the string if it was allocated
        icalmemory_free_buffer(str);

        // Free the component
        icalcomponent_free(component);
    }

    // Free the allocated input buffer
    free(input);

    return 0;
}