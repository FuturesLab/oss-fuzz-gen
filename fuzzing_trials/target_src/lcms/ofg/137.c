#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2_plugin.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated and non-empty
    char *format = (char *)malloc(size + 1);
    if (format == NULL) {
        cmsIT8Free(handle);
        return 0;
    }

    memcpy(format, data, size);
    format[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    cmsIT8DefineDblFormat(handle, format);

    // Clean up
    free(format);
    cmsIT8Free(handle);

    return 0;
}