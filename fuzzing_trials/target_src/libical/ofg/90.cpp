#include <cstdint> // For uint8_t
#include <cstddef> // For size_t
#include <cstring> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    // Create a buffer to hold the input data plus a null terminator
    char *ical_data = new char[size + 1];
    memcpy(ical_data, data, size);
    ical_data[size] = '\0'; // Null-terminate the input data

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Clean up the input buffer
    delete[] ical_data;

    // If parsing was successful, perform operations on the component
    if (component != NULL) {
        // Perform some operations on the component to increase coverage
        icalcomponent *subcomponent = icalcomponent_get_first_component(component, ICAL_ANY_COMPONENT);
        while (subcomponent != NULL) {
            // Do something with subcomponent
            subcomponent = icalcomponent_get_next_component(component, ICAL_ANY_COMPONENT);
        }

        // Clean up the component to prevent memory leaks
        icalcomponent_free(component);
    }

    return 0;
}