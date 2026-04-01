#include <cstdint>
#include <cstdlib>
#include <cstring> // Added to include memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Initialize a new icalcomponent from the input data
    icalcomponent *component = nullptr;

    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *buffer = static_cast<char *>(malloc(size + 1));
        if (buffer == nullptr) {
            return 0; // Memory allocation failed
        }

        // Copy the input data to the buffer and null-terminate it
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Parse the buffer into an icalcomponent
        component = icalparser_parse_string(buffer);

        // Free the temporary buffer
        free(buffer);
    }

    // Ensure the component is not NULL before calling the target function
    if (component != nullptr) {
        // Call the function-under-test
        int error_count = icalcomponent_count_errors(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    return 0;
}