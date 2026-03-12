#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    // Initialize a cmsContext variable
    cmsContext originalContext = cmsCreateContext(NULL, NULL);

    // Check if the originalContext is NULL, if so return early
    if (originalContext == NULL) {
        return 0;
    }

    // Create a non-NULL void pointer
    void *userData = (void *)data;

    // Call the function-under-test
    cmsContext duplicatedContext = cmsDupContext(originalContext, userData);

    // Clean up
    if (duplicatedContext != NULL) {
        cmsDeleteContext(duplicatedContext);
    }
    cmsDeleteContext(originalContext);

    return 0;
}