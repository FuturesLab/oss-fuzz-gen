#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_396(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsCIExyY whitePoint;
    cmsToneCurve *toneCurve = NULL;
    cmsHPROFILE profile = NULL;

    // Initialize whitePoint with some non-NULL values
    whitePoint.x = 0.3127;
    whitePoint.y = 0.3290;
    whitePoint.Y = 1.0;

    // Create a tone curve with a simple gamma value, ensuring it's non-NULL
    toneCurve = cmsBuildGamma(NULL, 2.2);
    if (toneCurve == NULL) {
        return 0;
    }

    // Call the function-under-test
    profile = cmsCreateGrayProfile(&whitePoint, toneCurve);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    if (toneCurve != NULL) {
        cmsFreeToneCurve(toneCurve);
    }

    return 0;
}