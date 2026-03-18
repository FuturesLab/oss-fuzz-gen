#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_274(const uint8_t *data, size_t size) {
    // Ensure there is enough data for at least one cmsColorSpaceSignature
    if (size < sizeof(cmsColorSpaceSignature)) {
        return 0;
    }

    // Extract cmsColorSpaceSignature from the input data
    cmsColorSpaceSignature colorSpace = *(cmsColorSpaceSignature*)data;

    // Initialize a cmsToneCurve array
    cmsToneCurve *toneCurves[1];
    toneCurves[0] = cmsBuildGamma(NULL, 2.2); // Using a standard gamma value

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateLinearizationDeviceLink(colorSpace, toneCurves);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsFreeToneCurve(toneCurves[0]);

    return 0;
}