#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a new icalproperty from the input data
    icalproperty *property = icalproperty_new_from_string(inputData);
    if (property != NULL) {
        // Call the function-under-test
        icalcomponent *parent = icalproperty_get_parent(property);

        // Clean up
        icalproperty_free(property);
    }

    free(inputData);
    return 0;
}