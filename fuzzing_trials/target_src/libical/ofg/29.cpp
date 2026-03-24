#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to store the input data as a string
    char *input_data = new char[size + 1];
    memcpy(input_data, data, size);
    input_data[size] = '\0';  // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_data);

    // Check if parsing was successful
    if (component != NULL) {
        // Call the function-under-test
        struct icaltimetype dtstamp = icalcomponent_get_dtstamp(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Clean up the temporary buffer
    delete[] input_data;

    return 0;
}