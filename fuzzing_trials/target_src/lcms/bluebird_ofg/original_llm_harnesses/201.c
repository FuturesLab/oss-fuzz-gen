#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsFloat32Number)) {
        return 0;
    }

    cmsToneCurve *toneCurve = cmsBuildGamma(NULL, 2.2); // Create a default tone curve
    if (toneCurve == NULL) {
        return 0;
    }

    cmsFloat32Number input = *((cmsFloat32Number *)data); // Use the first bytes as input value

    // Call the function-under-test
    cmsFloat32Number result = cmsEvalToneCurveFloat(toneCurve, input);

    // Clean up
    cmsFreeToneCurve(toneCurve);

    return 0;
}