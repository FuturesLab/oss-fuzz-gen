#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalcomponent_kind kind = icalcomponent_string_to_kind(null_terminated_data);

    // Clean up
    free(null_terminated_data);

    return 0;
}