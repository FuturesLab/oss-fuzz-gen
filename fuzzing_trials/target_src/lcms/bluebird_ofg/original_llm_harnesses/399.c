#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_399(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHTRANSFORM transform = NULL;
    cmsHPROFILE hProfile;
    cmsHPROFILE hProfile2;
    cmsContext context;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;

    // Create profiles
    hProfile = cmsCreate_sRGBProfile();
    hProfile2 = cmsCreate_sRGBProfile();

    if (hProfile == NULL || hProfile2 == NULL) {
        return 0;
    }

    // Create a transform
    transform = cmsCreateTransform(hProfile, TYPE_RGB_8, hProfile2, TYPE_RGB_8, intent, flags);

    if (transform == NULL) {
        cmsCloseProfile(hProfile);
        cmsCloseProfile(hProfile2);
        return 0;
    }

    // Call the function-under-test
    context = cmsGetTransformContextID(transform);

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(hProfile);
    cmsCloseProfile(hProfile2);

    return 0;
}