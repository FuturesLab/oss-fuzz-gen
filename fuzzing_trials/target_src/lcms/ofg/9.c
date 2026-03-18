#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    cmsHANDLE handle = NULL;

    // Initialize the handle using a non-NULL value
    // For fuzzing, we assume the handle is a valid pointer
    // In a real scenario, this should be a valid cmsHANDLE object
    if (size >= sizeof(cmsHANDLE)) {
        handle = (cmsHANDLE)data; // Cast data to cmsHANDLE for testing
    } else {
        // Allocate memory for handle if size is insufficient
        handle = (cmsHANDLE)malloc(sizeof(cmsHANDLE));
    }

    // Call the function-under-test
    cmsGBDFree(handle);

    // Free allocated memory if necessary
    if (size < sizeof(cmsHANDLE)) {
        free(handle);
    }

    return 0;
}