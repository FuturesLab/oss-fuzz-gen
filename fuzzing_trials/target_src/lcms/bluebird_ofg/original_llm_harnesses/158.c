#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Declare and initialize the input parameter for the function-under-test
    cmsFloat64Number adaptationState = 0.0;

    // Ensure that the size of the input data is sufficient to extract a cmsFloat64Number
    if (size >= sizeof(cmsFloat64Number)) {
        // Copy the data into the adaptationState variable
        adaptationState = *((const cmsFloat64Number*)data);
    }

    // Call the function-under-test
    cmsFloat64Number result = cmsSetAdaptationState(adaptationState);

    // Return 0 to indicate successful execution
    return 0;
}