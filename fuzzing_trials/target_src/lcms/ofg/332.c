#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    // Create a non-NULL cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Ensure that the context is valid
    if (context != NULL) {
        // Call the function-under-test
        cmsDeleteContext(context);
    }

    return 0;
}