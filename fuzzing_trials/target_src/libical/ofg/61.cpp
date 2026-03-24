#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/ical.h> // Adjust the include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure size is non-zero for valid memory allocation
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input buffer
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    // Copy the data to the input buffer and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);

    // Ensure the component is not NULL before passing it to the function
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_strip_errors(component);

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated input buffer
    free(input);

    return 0;
}