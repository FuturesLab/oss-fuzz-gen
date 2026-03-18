#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize a cmsContext variable
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Ensure the context is not NULL
    if (context == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsUnregisterPluginsTHR(context);

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}