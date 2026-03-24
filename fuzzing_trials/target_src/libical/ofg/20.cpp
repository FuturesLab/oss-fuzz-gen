#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary string buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the input data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(buffer);

    if (comp != nullptr) {
        // Call the function-under-test
        icalcomponent *parent = icalcomponent_get_parent(comp);

        // Clean up the icalcomponent
        icalcomponent_free(comp);
    }

    // Free the buffer
    free(buffer);

    return 0;
}