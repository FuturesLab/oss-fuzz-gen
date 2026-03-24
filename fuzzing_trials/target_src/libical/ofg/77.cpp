#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the input data
    char *input = (char *)malloc(size + 1);
    if (input == nullptr) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalcomponent
    component = icalparser_parse_string(input);

    // If parsing was successful, call the function-under-test
    if (component != nullptr) {
        icalproperty_status status = icalcomponent_get_status(component);

        // Use the status in some way to prevent compiler optimizations from removing the call
        if (status == ICAL_STATUS_NONE) {
            // Do something with the status if needed
        }

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated input string
    free(input);

    return 0;
}