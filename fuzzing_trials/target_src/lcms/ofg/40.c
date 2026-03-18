#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsToneCurve *toneCurve = NULL;
    cmsFloat64Number smoothFactor = 1.0;

    // Ensure the data size is sufficient to create a tone curve
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Create a tone curve using the data
    toneCurve = cmsBuildGamma(NULL, 2.2); // Example gamma value

    // Extract a double value from the input data to use as the smooth factor
    smoothFactor = *((cmsFloat64Number*)data);

    // Call the function-under-test
    cmsBool result = cmsSmoothToneCurve(toneCurve, smoothFactor);

    // Clean up
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}