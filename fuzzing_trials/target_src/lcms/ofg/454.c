#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_454(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsCIExyY whitePoint;
    cmsCIExyYTRIPLE primaries;
    cmsToneCurve *toneCurves[3];

    // Ensure data is large enough to initialize the parameters
    if (size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE) + 3 * sizeof(double)) {
        return 0;
    }

    // Initialize whitePoint from data
    whitePoint.x = ((double *)data)[0];
    whitePoint.y = ((double *)data)[1];
    whitePoint.Y = ((double *)data)[2];
    data += sizeof(cmsCIExyY);

    // Initialize primaries from data
    primaries.Red.x = ((double *)data)[0];
    primaries.Red.y = ((double *)data)[1];
    primaries.Red.Y = ((double *)data)[2];
    primaries.Green.x = ((double *)data)[3];
    primaries.Green.y = ((double *)data)[4];
    primaries.Green.Y = ((double *)data)[5];
    primaries.Blue.x = ((double *)data)[6];
    primaries.Blue.y = ((double *)data)[7];
    primaries.Blue.Y = ((double *)data)[8];
    data += sizeof(cmsCIExyYTRIPLE);

    // Initialize toneCurves with valid pointers
    for (int i = 0; i < 3; i++) {
        toneCurves[i] = cmsBuildGamma(NULL, 2.2);  // Example gamma value
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateRGBProfile(&whitePoint, &primaries, toneCurves);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    for (int i = 0; i < 3; i++) {
        if (toneCurves[i] != NULL) {
            cmsFreeToneCurve(toneCurves[i]);
        }
    }

    return 0;
}