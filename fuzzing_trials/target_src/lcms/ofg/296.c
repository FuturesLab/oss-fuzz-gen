#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context;
    cmsFloat64Number adaptationState;

    // Ensure there is enough data to read
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Create a new context
    context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Set adaptationState from data
    adaptationState = *(cmsFloat64Number *)(data);

    // Call the function-under-test
    cmsFloat64Number result = cmsSetAdaptationStateTHR(context, adaptationState);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile cmsFloat64Number use_result = result;
    (void)use_result;

    // Free the context
    cmsDeleteContext(context);

    return 0;
}