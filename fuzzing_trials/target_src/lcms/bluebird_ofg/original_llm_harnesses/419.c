#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_419(const uint8_t *data, size_t size) {
    cmsContext context;
    cmsHANDLE handle;

    // Initialize the context with some non-NULL value
    context = cmsCreateContext(NULL, NULL);

    // Call the function-under-test
    handle = cmsIT8Alloc(context);

    // Clean up
    if (handle != NULL) {
        cmsIT8Free(handle);
    }

    cmsDeleteContext(context);

    return 0;
}