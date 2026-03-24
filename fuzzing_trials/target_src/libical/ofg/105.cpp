#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = nullptr;

    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = new char[size + 1];
    std::memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Parse the input data into an iCalendar component
    component = icalparser_parse_string(buffer);

    // If parsing was successful, get the summary
    if (component != nullptr) {
        const char *summary = icalcomponent_get_summary(component);

        // Optionally, print the summary for debugging purposes
        if (summary != nullptr) {
            printf("Summary: %s\n", summary);
        }

        // Free the component
        icalcomponent_free(component);
    }

    // Clean up
    delete[] buffer;

    return 0;
}