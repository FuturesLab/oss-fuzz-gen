#include <stdint.h>
#include <lcms2.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = (cmsContext)data;  // Casting data to cmsContext for fuzzing
    cmsCIExyY whitePoint;
    cmsCIExyYTRIPLE primaries;
    cmsToneCurve* toneCurves[3];

    // Ensure data is sufficient for fuzzing
    if (size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE) + 3 * sizeof(cmsToneCurve*)) {
        return 0;
    }

    // Initialize whitePoint
    whitePoint.x = *(double*)data;
    whitePoint.y = *(double*)(data + sizeof(double));
    whitePoint.Y = *(double*)(data + 2 * sizeof(double));

    // Initialize primaries
    primaries.Red.x = *(double*)(data + 3 * sizeof(double));
    primaries.Red.y = *(double*)(data + 4 * sizeof(double));
    primaries.Red.Y = *(double*)(data + 5 * sizeof(double));
    primaries.Green.x = *(double*)(data + 6 * sizeof(double));
    primaries.Green.y = *(double*)(data + 7 * sizeof(double));
    primaries.Green.Y = *(double*)(data + 8 * sizeof(double));
    primaries.Blue.x = *(double*)(data + 9 * sizeof(double));
    primaries.Blue.y = *(double*)(data + 10 * sizeof(double));
    primaries.Blue.Y = *(double*)(data + 11 * sizeof(double));

    // Initialize toneCurves
    for (int i = 0; i < 3; i++) {
        toneCurves[i] = cmsBuildGamma(context, 2.2);  // Example gamma value, replace with appropriate logic if needed
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateRGBProfileTHR(context, &whitePoint, &primaries, toneCurves);

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