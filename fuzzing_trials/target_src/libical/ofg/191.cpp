#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstring> // Include for memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_191(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for safe string operations
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (!inputData) {
        return 0; // Return if memory allocation fails
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(inputData);

    // Perform operations on the component if it's valid
    if (component != NULL) {
        // Example operation: Convert component to a string and back
        char *componentStr = icalcomponent_as_ical_string(component);
        if (componentStr) {
            icalcomponent *newComponent = icalparser_parse_string(componentStr);
            if (newComponent) {
                icalcomponent_free(newComponent);
            }
        }

        // Free the initial component
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(inputData);

    return 0;
}