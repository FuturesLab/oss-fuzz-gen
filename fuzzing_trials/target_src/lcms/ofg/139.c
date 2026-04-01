#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to extract parameters
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Initialize the parameters for cmsIT8SetDataFormat
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract an integer from the data
    int index = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Use the remaining data as a string for the format
    char *format = (char *)malloc(size + 1);
    if (format == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(format, data, size);
    format[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    cmsBool result = cmsIT8SetDataFormat(handle, index, format);

    // Clean up
    free(format);
    cmsIT8Free(handle);

    return 0;
}