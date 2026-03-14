#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Create a profile from the input data
    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);
    if (profile == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Create a transform using the profile
    cmsHTRANSFORM transform = cmsCreateTransform(profile, TYPE_RGB_8, profile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (transform == NULL) {
        cmsCloseProfile(profile);
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsNAMEDCOLORLIST *namedColorList = cmsGetNamedColorList(transform);

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(profile);
    cmsDeleteContext(context);

    return 0;
}