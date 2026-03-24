#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;

    // Ensure the size is appropriate for creating a component
    if (size > 0) {
        // Create a temporary string from the input data
        char *inputData = (char *)malloc(size + 1);
        if (inputData == nullptr) {
            return 0;
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data into an icalcomponent
        component = icalparser_parse_string(inputData);

        free(inputData);
    }

    if (component != nullptr) {
        // Call the function-under-test
        struct icaltime_span span = icalcomponent_get_span(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    return 0;
}