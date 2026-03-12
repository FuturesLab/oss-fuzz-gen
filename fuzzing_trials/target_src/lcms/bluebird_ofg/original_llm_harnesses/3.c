#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    cmsColorSpaceSignature colorSpace = cmsSigRgbData;
    if (size > 0) {
        colorSpace = (cmsColorSpaceSignature)(data[0] % 5); // Randomly select a color space signature
    }

    cmsToneCurve *toneCurves[3];
    for (int i = 0; i < 3; i++) {
        toneCurves[i] = cmsBuildGamma(context, 2.2); // Create a simple gamma curve
        if (toneCurves[i] == NULL) {
            cmsDeleteContext(context);
            return 0;
        }
    }

    cmsHPROFILE profile = cmsCreateLinearizationDeviceLinkTHR(context, colorSpace, (const cmsToneCurve **)toneCurves);

    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    for (int i = 0; i < 3; i++) {
        cmsFreeToneCurve(toneCurves[i]);
    }

    cmsDeleteContext(context);

    return 0;
}