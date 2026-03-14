#include <stdint.h>
#include <string.h> // For memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_297(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Extract a cmsFloat64Number from the input data
    cmsFloat64Number adaptationState;
    memcpy(&adaptationState, data, sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number result = cmsSetAdaptationStateTHR(context, adaptationState);

    // Clean up
    cmsDeleteContext(context);

    return 0;
}