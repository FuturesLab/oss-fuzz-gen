#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure the input data is treated as a string
    if (size == 0) {
        return 0; // Exit if size is zero to avoid unnecessary processing
    }

    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);

    // Free the input buffer
    free(input);

    // Perform any necessary operations on the component
    if (component != NULL) {
        // Example operation: convert the component to a string
        char *component_str = icalcomponent_as_ical_string(component);

        // Ensure the string is not NULL before using it
        if (component_str != NULL) {
            // Avoid printing in a fuzzing environment
            // Free the component string if it was allocated
            icalmemory_free_buffer(component_str);
        }

        // Free the component
        icalcomponent_free(component);
    }

    return 0;
}