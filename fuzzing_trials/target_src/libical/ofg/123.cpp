#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for creating a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to store the input data as a string
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == nullptr) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Free the temporary buffer
    free(ical_data);

    // If parsing was successful, call the function-under-test
    if (component != nullptr) {
        struct icaltimetype dtstart = icalcomponent_get_dtstart(component);

        // Optionally, you can perform additional operations with dtstart here

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    return 0;
}