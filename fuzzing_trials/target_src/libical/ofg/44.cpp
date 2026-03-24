#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    // Ensure the data is null-terminated for string operations
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);
    if (component != NULL) {
        // Call the function-under-test
        struct icaldurationtype duration = icalcomponent_get_duration(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated memory for input data
    free(inputData);

    return 0;
}