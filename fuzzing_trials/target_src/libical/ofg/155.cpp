#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "libical/icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalcomponent from the buffer
    icalcomponent *component = icalcomponent_new_from_string(buffer);

    // Ensure the component is not NULL before calling the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_kind kind = icalcomponent_isa(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(buffer);

    return 0;
}