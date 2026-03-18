#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters
    cmsHANDLE handle = cmsIT8Alloc(NULL); // Allocate a new IT8 handle
    if (handle == NULL) {
        return 0; // If allocation fails, exit early
    }

    int index = 0; // Initialize index to 0

    // Ensure the string is null-terminated and non-null
    char format[256];
    if (size > 0) {
        size_t copy_size = size < sizeof(format) - 1 ? size : sizeof(format) - 1;
        memcpy(format, data, copy_size);
        format[copy_size] = '\0'; // Null-terminate the string
    } else {
        format[0] = 'A'; // Default non-null value
        format[1] = '\0';
    }

    // Call the function-under-test
    cmsBool result = cmsIT8SetDataFormat(handle, index, format);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}