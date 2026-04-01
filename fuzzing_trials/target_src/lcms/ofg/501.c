#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_501(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsCIExyY whitePoint;
    cmsFloat64Number temperature;

    // Ensure there's enough data to read a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize temperature from input data
    temperature = *((cmsFloat64Number*)data);

    // Call the function-under-test
    cmsBool result = cmsWhitePointFromTemp(&whitePoint, temperature);

    // Use the result or whitePoint for further logic if needed
    // (For fuzzing, we just need to ensure the function is called)

    return 0;
}