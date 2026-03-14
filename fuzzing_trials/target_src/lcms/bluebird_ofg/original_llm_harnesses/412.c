#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_412(const uint8_t *data, size_t size) {
    // Initialize the cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Ensure that the input data is null-terminated to be used as a string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Copy the data into filename and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    cmsHANDLE handle = cmsIT8LoadFromFile(context, filename);

    // Clean up
    if (handle != NULL) {
        cmsIT8Free(handle);
    }

    free(filename);
    cmsDeleteContext(context);

    return 0;
}