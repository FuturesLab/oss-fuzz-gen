#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a cmsToneCurve
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Initialize a memory context
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create a tone curve with the given data
    cmsFloat64Number gamma = *((cmsFloat64Number*)data);
    cmsToneCurve* toneCurve = cmsBuildGamma(contextID, gamma);

    // Call the function under test
    if (toneCurve != NULL) {
        cmsBool result = cmsIsToneCurveLinear(toneCurve);

        // Clean up
        cmsFreeToneCurve(toneCurve);
    }

    // Delete the memory context
    cmsDeleteContext(contextID);

    return 0;
}