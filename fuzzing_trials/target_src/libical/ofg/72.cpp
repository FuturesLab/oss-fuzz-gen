#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <libical/ical.h> // Ensure libical is installed and linked properly

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the data is not empty and size is sufficient to avoid unnecessary operations
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data != NULL) {
            // Copy data into the temporary buffer and null-terminate it
            memcpy(temp_data, data, size);
            temp_data[size] = '\0';

            // Set a property with the data to the component
            icalcomponent_set_summary(component, temp_data);

            // Free the temporary buffer
            free(temp_data);
        }
    }

    // Call the function-under-test
    char *ical_string = icalcomponent_as_ical_string_r(component);

    // Output the result (for debugging purposes, can be removed in actual fuzzing)
    if (ical_string != NULL) {
        std::cout << ical_string << std::endl;
        icalmemory_free_buffer(ical_string);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}