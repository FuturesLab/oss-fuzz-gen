#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_455(const uint8_t *data, size_t size) {
    // Initialize the variables needed for cmsCreateRGBProfile
    cmsCIExyY whitePoint;
    cmsCIExyYTRIPLE primaries;
    cmsToneCurve *toneCurves[3];

    // Ensure the input size is sufficient for our needs
    if (size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE) + 3 * sizeof(void *)) {
        return 0;
    }

    // Fill the whitePoint from the input data
    whitePoint.x = (double)data[0] / 255.0;
    whitePoint.y = (double)data[1] / 255.0;
    whitePoint.Y = (double)data[2] / 255.0;

    // Fill the primaries from the input data
    primaries.Red.x = (double)data[3] / 255.0;
    primaries.Red.y = (double)data[4] / 255.0;
    primaries.Red.Y = (double)data[5] / 255.0;
    primaries.Green.x = (double)data[6] / 255.0;
    primaries.Green.y = (double)data[7] / 255.0;
    primaries.Green.Y = (double)data[8] / 255.0;
    primaries.Blue.x = (double)data[9] / 255.0;
    primaries.Blue.y = (double)data[10] / 255.0;
    primaries.Blue.Y = (double)data[11] / 255.0;

    // Initialize tone curves
    for (int i = 0; i < 3; ++i) {
        toneCurves[i] = cmsBuildGamma(NULL, 2.2);  // Using a standard gamma value
        if (toneCurves[i] == NULL) {
            // Clean up if tone curve creation fails
            for (int j = 0; j < i; ++j) {
                cmsFreeToneCurve(toneCurves[j]);
            }
            return 0;
        }
    }

    // Call the function under test
    cmsHPROFILE profile = cmsCreateRGBProfile(&whitePoint, &primaries, toneCurves);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    for (int i = 0; i < 3; ++i) {
        cmsFreeToneCurve(toneCurves[i]);
    }

    return 0;
}