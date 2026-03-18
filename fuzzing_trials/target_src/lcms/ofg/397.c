#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_397(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize cmsCIExyY
    if (size < 3) { // We need at least 3 bytes for cmsCIExyY initialization
        return 0;
    }

    // Initialize cmsCIExyY
    cmsCIExyY whitePoint;
    whitePoint.x = (double)data[0] / 255.0; // Normalize to [0, 1]
    whitePoint.y = (double)data[1] / 255.0; // Normalize to [0, 1]
    whitePoint.Y = (double)data[2] / 255.0; // Normalize to [0, 1]

    // Initialize cmsToneCurve
    cmsToneCurve *grayToneCurve = cmsBuildGamma(NULL, 2.2); // Using a gamma value as an example

    // Call the function under test
    cmsHPROFILE profile = cmsCreateGrayProfile(&whitePoint, grayToneCurve);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    if (grayToneCurve != NULL) {
        cmsFreeToneCurve(grayToneCurve);
    }

    return 0;
}