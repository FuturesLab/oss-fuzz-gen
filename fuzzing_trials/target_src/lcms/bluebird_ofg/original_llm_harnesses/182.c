#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsCIExyY) + sizeof(double)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsCIExyY whitePoint;
    cmsToneCurve *toneCurve;

    // Use the input data to initialize cmsCIExyY structure
    whitePoint.x = ((double*)data)[0];
    whitePoint.y = ((double*)data)[1];
    whitePoint.Y = ((double*)data)[2];

    // Create a tone curve with a gamma value derived from input data
    double gamma = ((double*)data)[3];
    toneCurve = cmsBuildGamma(context, gamma);
    if (toneCurve == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateGrayProfileTHR(context, &whitePoint, toneCurve);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsFreeToneCurve(toneCurve);
    cmsDeleteContext(context);

    return 0;
}