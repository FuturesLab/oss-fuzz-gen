#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VTODO_COMPONENT);

    // Ensure the data is not empty and is large enough to be meaningful
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data == NULL) {
            icalcomponent_free(component);
            return 0;
        }

        // Copy the data into the temporary buffer and null-terminate it
        memcpy(temp_data, data, size);
        temp_data[size] = '\0';

        // Parse the data into the icalcomponent
        icalcomponent *parsed_component = icalparser_parse_string(temp_data);
        free(temp_data);

        if (parsed_component != NULL) {
            // Call the function-under-test
            struct icaltimetype due_time = icalcomponent_get_due(parsed_component);

            // Free the parsed component
            icalcomponent_free(parsed_component);
        }
    }

    // Free the original component
    icalcomponent_free(component);

    return 0;
}