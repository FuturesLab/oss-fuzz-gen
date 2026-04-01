#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent from the input data
    icalcomponent *component = nullptr;

    // Ensure the size is reasonable to prevent excessive memory usage
    if (size > 0 && size < 1024) {
        // Create an icalcomponent from the input data
        char *input_data = (char *)malloc(size + 1);
        if (input_data != nullptr) {
            memcpy(input_data, data, size);
            input_data[size] = '\0'; // Null-terminate the string

            component = icalparser_parse_string(input_data);
            free(input_data);
        }
    }

    // Call the function-under-test
    if (component != nullptr) {
        icalcomponent_convert_errors(component);
        icalcomponent_free(component);
    }

    return 0;
}