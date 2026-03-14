#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a cmsToneCurve
    if (size < sizeof(cmsFloat32Number)) {
        return 0;
    }

    // Create a memory context for the tone curve
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Allocate a tone curve using the provided data
    cmsFloat32Number gamma = *((cmsFloat32Number *)data);
    cmsToneCurve *toneCurve = cmsBuildGamma(context, gamma);

    // Ensure the tone curve is created successfully
    if (toneCurve == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsInt32Number parametricType = cmsGetToneCurveParametricType(toneCurve);

    // Clean up
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(context);

    return 0;
}