#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    // Copy data into the input buffer and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_from_string(input);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    free(input);

    return 0;
}