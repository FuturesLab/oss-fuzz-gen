#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsColorSpaceSignature colorSpace = cmsSigRgbData;
    cmsToneCurve *toneCurves[3];

    // Create tone curves for each channel (assuming RGB for simplicity)
    for (int i = 0; i < 3; i++) {
        toneCurves[i] = cmsBuildGamma(context, 2.2); // Using a gamma of 2.2 as an example
        if (toneCurves[i] == NULL) {
            // Clean up and return if tone curve creation fails
            for (int j = 0; j < i; j++) {
                cmsFreeToneCurve(toneCurves[j]);
            }
            cmsDeleteContext(context);
            return 0;
        }
    }

    // Call the function under test
    cmsHPROFILE profile = cmsCreateLinearizationDeviceLinkTHR(context, colorSpace, (const cmsToneCurve **)toneCurves);

    // Check the result and clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    for (int i = 0; i < 3; i++) {
        cmsFreeToneCurve(toneCurves[i]);
    }
    cmsDeleteContext(context);

    return 0;
}