#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include string.h for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_364(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create a tone curve with a single gamma value
    cmsFloat64Number gammaValue = 2.2; // A typical gamma value
    cmsToneCurve *toneCurve = cmsBuildGamma(contextID, gammaValue);

    // Extract a cmsFloat64Number from the input data
    cmsFloat64Number inputNumber;
    memcpy(&inputNumber, data, sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsFloat64Number estimatedGamma = cmsEstimateGamma(toneCurve, inputNumber);

    // Clean up
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(contextID);

    return 0;
}