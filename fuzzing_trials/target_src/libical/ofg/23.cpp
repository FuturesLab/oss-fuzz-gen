#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for memcpy

extern "C" {
    // Wrap the ical headers in extern "C" to ensure proper linkage
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent structure
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);

    // Ensure the data is not empty
    if (size > 0) {
        // Create a string from the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == nullptr) {
            return 0; // Memory allocation failed
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data to create an icalcomponent
        icalcomponent *parsedComponent = icalparser_parse_string(inputData);
        if (parsedComponent != nullptr) {
            // Get the component name
            const char *componentName = icalcomponent_get_component_name(parsedComponent);

            // Use the componentName for further processing or testing
            // In this case, we just ensure the function is called
            if (componentName != nullptr) {
                // Do something with componentName if needed
            }

            // Free the parsed component
            icalcomponent_free(parsedComponent);
        }

        // Free the input data
        free(inputData);
    }

    // Free the initial component
    icalcomponent_free(component);

    return 0;
}