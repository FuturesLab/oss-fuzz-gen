#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Initialize the parameters for cmsCreateRGBProfileTHR
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Ensure data is large enough for our needs
    if (size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE) + 3 * sizeof(cmsToneCurve *)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Initialize cmsCIExyY
    cmsCIExyY whitePoint;
    whitePoint.x = (double)data[0] / UINT8_MAX;
    whitePoint.y = (double)data[1] / UINT8_MAX;
    whitePoint.Y = (double)data[2] / UINT8_MAX;

    // Initialize cmsCIExyYTRIPLE
    cmsCIExyYTRIPLE primaries;
    primaries.Red.x = (double)data[3] / UINT8_MAX;
    primaries.Red.y = (double)data[4] / UINT8_MAX;
    primaries.Red.Y = (double)data[5] / UINT8_MAX;

    primaries.Green.x = (double)data[6] / UINT8_MAX;
    primaries.Green.y = (double)data[7] / UINT8_MAX;
    primaries.Green.Y = (double)data[8] / UINT8_MAX;

    primaries.Blue.x = (double)data[9] / UINT8_MAX;
    primaries.Blue.y = (double)data[10] / UINT8_MAX;
    primaries.Blue.Y = (double)data[11] / UINT8_MAX;

    // Initialize cmsToneCurve pointers
    cmsToneCurve *toneCurves[3];
    for (int i = 0; i < 3; i++) {
        toneCurves[i] = cmsBuildGamma(context, 2.2); // Using a default gamma value
    }

    // Call the function under test
    cmsHPROFILE profile = cmsCreateRGBProfileTHR(context, &whitePoint, &primaries, (const cmsToneCurve **)toneCurves);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    for (int i = 0; i < 3; i++) {
        if (toneCurves[i] != NULL) {
            cmsFreeToneCurve(toneCurves[i]);
        }
    }
    cmsDeleteContext(context);

    return 0;
}