#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsUInt32Number nPoints = 256; // Example value for the number of points

    // Ensure the data is large enough to create a cmsToneCurve
    if (size < nPoints * sizeof(cmsFloat32Number)) {
        return 0;
    }

    // Create a memory context for the tone curve
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Create a tone curve from the profile
    cmsToneCurve *toneCurve = cmsReadTag(hProfile, cmsSigGrayTRCTag);
    if (toneCurve == NULL) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Fuzz the cmsReverseToneCurveEx function
    cmsToneCurve *reversedToneCurve = cmsReverseToneCurveEx(nPoints, toneCurve);

    // Clean up
    if (reversedToneCurve != NULL) {
        cmsFreeToneCurve(reversedToneCurve);
    }
    cmsFreeToneCurve(toneCurve);
    cmsCloseProfile(hProfile);

    return 0;
}