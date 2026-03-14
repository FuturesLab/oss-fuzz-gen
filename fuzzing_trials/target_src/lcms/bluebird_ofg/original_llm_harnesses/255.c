#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    if (size < 3) {
        // Not enough data to proceed
        return 0;
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number nProfiles = 2; // Number of profiles
    cmsUInt32Number inputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number outputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number intent = INTENT_PERCEPTUAL; // Example intent
    cmsUInt32Number flags = 0; // Example flags

    // Allocate memory for profiles
    cmsHPROFILE *profiles = (cmsHPROFILE *)malloc(nProfiles * sizeof(cmsHPROFILE));
    if (profiles == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Initialize profiles with dummy profiles
    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        profiles[i] = cmsCreate_sRGBProfile();
        if (profiles[i] == NULL) {
            // Clean up and exit if profile creation fails
            for (cmsUInt32Number j = 0; j < i; j++) {
                cmsCloseProfile(profiles[j]);
            }
            free(profiles);
            cmsDeleteContext(context);
            return 0;
        }
    }

    // Call the function under test
    cmsHTRANSFORM transform = cmsCreateMultiprofileTransformTHR(context, profiles, nProfiles, inputFormat, outputFormat, intent, flags);

    // If a transform is created, use it to process the input data
    if (transform != NULL) {
        uint8_t input[3] = {data[0], data[1], data[2]};
        uint8_t output[3];
        cmsDoTransform(transform, input, output, 1);
        cmsDeleteTransform(transform);
    }

    // Clean up
    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        cmsCloseProfile(profiles[i]);
    }
    free(profiles);
    cmsDeleteContext(context);

    return 0;
}