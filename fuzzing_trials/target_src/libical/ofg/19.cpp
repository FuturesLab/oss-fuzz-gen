#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Create a temporary memory buffer to hold the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // If parsing was successful, get the parent of the component
    if (component != NULL) {
        icalcomponent *parent = icalcomponent_get_parent(component);
        
        // Normally, you would do something with the parent here
        // For fuzzing, we just ensure the function is called

        // Free the component after use
        icalcomponent_free(component);
    }

    // Free the buffer
    free(buffer);

    return 0;
}