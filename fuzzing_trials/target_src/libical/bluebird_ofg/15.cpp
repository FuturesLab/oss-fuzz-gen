#include <cstdint> // Include standard library for uint8_t
#include <cstddef> // Include standard library for size_t
#include <cstring> // Include standard library for strlen

extern "C" {
#include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and is null-terminated
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) return 0;
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Create an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(inputData);
    free(inputData); // Free the allocated memory for inputData
    if (component == NULL) return 0;

    // Define a callback function for icalcomponent_foreach_tzid
    auto callback = [](icalparameter *param, void *user_data) {
        // Do nothing in the callback for now
    };

    // Call the function-under-test
    icalcomponent_foreach_tzid(component, callback, nullptr);

    // Clean up
    icalcomponent_free(component);

    return 0;
}