#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for creating a string
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the data as a null-terminated string
    char *buffer = new char[size + 1];
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Convert the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Check if the component was created successfully
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_strip_errors(component);

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Clean up the buffer
    delete[] buffer;

    return 0;
}