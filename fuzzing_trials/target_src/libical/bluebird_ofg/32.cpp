#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow issues
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        return 0; // If memory allocation fails, return early
    }
    
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the string

    // Initialize an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    // If the component is successfully created, call the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        icalproperty_status status = icalcomponent_get_status(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated memory for the null-terminated data
    free(null_terminated_data);

    return 0;
}