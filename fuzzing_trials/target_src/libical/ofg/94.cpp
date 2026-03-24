#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t
#include <cstdlib>  // For malloc and free
#include <cstring>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = nullptr;
    
    // Ensure the input size is non-zero and manageable
    if (size > 0 && size < 1024) {
        // Convert input data to a string
        char *inputData = (char *)malloc(size + 1);
        if (inputData == nullptr) {
            return 0;
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0';

        // Parse the input data to create an icalcomponent
        component = icalparser_parse_string(inputData);

        // Free the allocated memory for inputData
        free(inputData);
    }

    // Call the function-under-test
    if (component != nullptr) {
        icalcomponent *currentComponent = icalcomponent_get_current_component(component);

        // Perform any necessary operations on currentComponent
        // (In a fuzzing context, this is typically not required)

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    return 0;
}