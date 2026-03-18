#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Removed 'extern "C"' as it is not needed in C code
int LLVMFuzzerTestOneInput_436(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for cmsCreateMultiprofileTransform
    cmsHPROFILE profiles[3];
    cmsUInt32Number nProfiles = 3;
    cmsUInt32Number inputFormat = TYPE_RGB_8;
    cmsUInt32Number outputFormat = TYPE_RGB_8;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;

    // Create sample profiles for testing
    profiles[0] = cmsCreate_sRGBProfile();
    profiles[1] = cmsCreateLab4Profile(NULL);
    profiles[2] = cmsCreateXYZProfile();

    // Call the function-under-test
    cmsHTRANSFORM transform = cmsCreateMultiprofileTransform(
        profiles, nProfiles, inputFormat, outputFormat, intent, flags);

    // Clean up
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }

    for (cmsUInt32Number i = 0; i < nProfiles; i++) {
        if (profiles[i] != NULL) {
            cmsCloseProfile(profiles[i]);
        }
    }

    return 0;
}