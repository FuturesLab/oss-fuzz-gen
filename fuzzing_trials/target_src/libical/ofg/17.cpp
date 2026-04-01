#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;

    // Ensure that the size is sufficient to create a valid icalcomponent
    if (size > 0) {
        // Create a temporary string buffer to hold the input data
        char *icalData = (char *)malloc(size + 1);
        if (icalData == nullptr) {
            return 0; // Memory allocation failed
        }

        // Copy the input data into the buffer and null-terminate it
        memcpy(icalData, data, size);
        icalData[size] = '\0';

        // Parse the ical data to create an icalcomponent
        component = icalparser_parse_string(icalData);

        // Free the temporary buffer
        free(icalData);
    }

    if (component != nullptr) {
        // Call the function-under-test
        struct icaltimetype recurrenceId = icalcomponent_get_recurrenceid(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    return 0;
}