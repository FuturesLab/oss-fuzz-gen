#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated before passing it to icalcomponent_new_from_string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Return early if memory allocation fails
    }

    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize a icalcomponent object
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    // Free the allocated memory for the null-terminated data
    free(null_terminated_data);

    // Check if the component was created successfully
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_normalize(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    return 0;
}