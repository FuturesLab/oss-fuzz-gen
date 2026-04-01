#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Initialize a cmsContext with some non-NULL value
    cmsContext context = cmsCreateContext(NULL, NULL);

    if (context == NULL) {
        return 0; // Early exit if context creation fails
    }

    // Call the function-under-test
    void *userData = cmsGetContextUserData(context);

    // Use the data for further operations if needed
    // For example, you might want to simulate some operations with userData

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}