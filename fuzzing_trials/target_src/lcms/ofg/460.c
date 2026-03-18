#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_460(const uint8_t *data, size_t size) {
    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Check if the size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Create a profile from the input data
    cmsHPROFILE profile = cmsOpenProfileFromMemTHR(context, data, size);

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Perform operations on the profile to increase code coverage
        cmsUInt32Number intent = INTENT_PERCEPTUAL; // Corrected to use the right constant
        cmsHPROFILE dstProfile = cmsCreate_sRGBProfileTHR(context);
        cmsHTRANSFORM transform = cmsCreateTransformTHR(context, profile, TYPE_RGB_8, dstProfile, TYPE_RGB_8, intent, 0);

        // Use the transform to process some data
        if (transform != NULL) {
            uint8_t input[3] = {0, 0, 0};
            uint8_t output[3];
            cmsDoTransform(transform, input, output, 1);
            cmsDeleteTransform(transform);
        }

        cmsCloseProfile(dstProfile);
        cmsCloseProfile(profile);
    }

    cmsDeleteContext(context);

    return 0;
}