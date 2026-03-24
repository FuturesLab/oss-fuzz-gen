#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely use it as a string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);

    // Perform operations on the component if necessary
    // For this fuzzing harness, we simply parse the input and then clean up

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    free(input);

    return 0;
}