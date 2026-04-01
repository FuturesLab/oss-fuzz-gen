#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a new icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(inputData);

    // If the component creation was successful, call the function-under-test
    if (component != NULL) {
        const char *x_name = icalcomponent_get_x_name(component);
        // Optionally, you can do something with x_name, like logging or asserting
    }

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    free(inputData);

    return 0;
}