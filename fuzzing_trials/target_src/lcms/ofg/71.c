#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    cmsToneCurve *toneCurve = NULL;

    // Ensure there is enough data to create a tone curve
    if (size < sizeof(cmsFloat32Number)) {
        return 0;
    }

    // Create a tone curve from the input data
    // Use the first part of the data as the number of segments
    cmsFloat32Number gamma = *((cmsFloat32Number *)data);
    toneCurve = cmsBuildGamma(NULL, gamma);

    if (toneCurve != NULL) {
        // Call the function under test
        cmsBool result = cmsIsToneCurveDescending(toneCurve);

        // Clean up
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}