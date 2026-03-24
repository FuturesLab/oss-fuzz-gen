#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for ical.h
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Initialize a memory buffer with the input data
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0'; // Null-terminate the input data

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_data);

    // Ensure the component is not NULL before calling the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent *first_real_component = icalcomponent_get_first_real_component(component);

        // Optionally perform some operations on the result
        if (first_real_component != NULL) {
            // Example operation: get the component type
            icalcomponent_kind kind = icalcomponent_isa(first_real_component);
        }

        // Free the parsed icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(input_data);

    return 0;
}