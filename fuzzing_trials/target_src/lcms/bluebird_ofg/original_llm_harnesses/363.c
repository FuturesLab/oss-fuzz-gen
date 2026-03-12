#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_363(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Create a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a tone curve with a single gamma value
    cmsFloat64Number gammaValue = 2.2; // Example gamma value
    cmsToneCurve *toneCurve = cmsBuildGamma(context, gammaValue);

    // Extract a cmsFloat64Number from the input data
    cmsFloat64Number inputNumber;
    memcpy(&inputNumber, data, sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number estimatedGamma = cmsEstimateGamma(toneCurve, inputNumber);

    // Clean up
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(context);

    return 0;
}