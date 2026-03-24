#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>     // Include for malloc and free
#include <string.h>     // Include for memcpy
#include <libical/ical.h>  // Include the libical header for icalcomponent and icaltimetype

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = nullptr;

    // Ensure that the input data is not empty
    if (size > 0) {
        // Convert input data to a string
        char *input_data = (char *)malloc(size + 1);
        if (input_data == nullptr) {
            return 0; // Memory allocation failed
        }
        memcpy(input_data, data, size);
        input_data[size] = '\0';

        // Parse the input data into an icalcomponent
        component = icalparser_parse_string(input_data);
        
        // Free the allocated input data
        free(input_data);
    }

    if (component != nullptr) {
        // Call the function-under-test
        struct icaltimetype due_time = icalcomponent_get_due(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    return 0;
}