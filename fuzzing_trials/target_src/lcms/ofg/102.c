#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a cmsContext
    if (size < sizeof(cmsContext)) {
        return 0;
    }

    // Copy the input data to a separate buffer to avoid modifying the const input
    uint8_t *data_copy = (uint8_t *)malloc(size);
    if (data_copy == NULL) {
        return 0; // Handle memory allocation failure
    }
    memcpy(data_copy, data, size);

    // Initialize a cmsContext from the copied data
    cmsContext context = (cmsContext)(uintptr_t)data_copy;

    // Call the function under test
    cmsUnregisterPluginsTHR(context);

    // Free the copied data
    free(data_copy);

    return 0;
}