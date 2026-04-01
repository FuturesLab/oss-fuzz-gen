#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputData);
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent *realComponent = icalcomponent_get_first_real_component(component);

        // Clean up
        icalcomponent_free(component);
    }

    free(inputData);
    return 0;
}