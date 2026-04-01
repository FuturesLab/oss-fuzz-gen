#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_366(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char **properties = NULL;

    // Initialize the handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0; // If allocation fails, just return
    }

    // Call the function-under-test
    cmsUInt32Number result = cmsIT8EnumProperties(handle, &properties);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}