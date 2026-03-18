#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    // Initialize the source context
    cmsContext srcContext = cmsCreateContext(NULL, NULL);
    if (srcContext == NULL) {
        return 0;
    }

    // Use the data as a pointer to pass to the function
    void *userData = (void *)data;

    // Call the function-under-test
    cmsContext dupContext = cmsDupContext(srcContext, userData);

    // Clean up
    if (dupContext != NULL) {
        cmsDeleteContext(dupContext);
    }
    cmsDeleteContext(srcContext);

    return 0;
}