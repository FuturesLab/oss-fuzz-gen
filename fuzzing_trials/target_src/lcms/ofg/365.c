#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_365(const uint8_t *data, size_t size) {
    // Initialize a cmsHANDLE
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Allocate memory for the properties array
    char **properties = (char **)malloc(sizeof(char *) * 10); // Allocate space for 10 char* pointers
    if (properties == NULL) {
        cmsIT8Free(handle);
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number result = cmsIT8EnumProperties(handle, &properties);

    // Clean up
    free(properties);
    cmsIT8Free(handle);

    return 0;
}