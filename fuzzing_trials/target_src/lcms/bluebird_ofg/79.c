#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    cmsContext context;
    cmsHANDLE handle;

    // Initialize the context with a non-null value
    context = cmsCreateContext(NULL, NULL);

    // Call the function-under-test
    handle = cmsGBDAlloc(context);

    // Clean up
    if (handle != NULL) {
        cmsGBDFree(handle);
    }
    cmsDeleteContext(context);

    return 0;
}