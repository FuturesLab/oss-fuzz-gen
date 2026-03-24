#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use as a C-string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Memory allocation failed, exit early
    }

    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_from_string(input);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    free(input);

    return 0;
}