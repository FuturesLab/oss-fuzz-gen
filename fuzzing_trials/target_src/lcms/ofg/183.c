#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = (cmsContext)1; // Dummy non-NULL context
    cmsCIExyY whitePoint;
    cmsToneCurve *toneCurve = NULL;
    cmsHPROFILE profile = NULL;

    // Ensure the data size is sufficient for initializing cmsCIExyY
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Initialize cmsCIExyY from input data
    whitePoint.x = *((const double *)data);
    whitePoint.y = *((const double *)(data + sizeof(double)));
    whitePoint.Y = *((const double *)(data + 2 * sizeof(double)));

    // Create a tone curve with a simple gamma value
    toneCurve = cmsBuildGamma(context, 2.2); // Using a gamma of 2.2 as an example

    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    profile = cmsCreateGrayProfileTHR(context, &whitePoint, toneCurve);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsFreeToneCurve(toneCurve);

    return 0;
}