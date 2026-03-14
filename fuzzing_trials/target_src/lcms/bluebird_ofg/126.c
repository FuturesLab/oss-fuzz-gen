#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Initialize a dummy color transform
    cmsHTRANSFORM transform = NULL;
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    
    if (inputProfile == NULL || outputProfile == NULL) {
        if (inputProfile != NULL) cmsCloseProfile(inputProfile);
        if (outputProfile != NULL) cmsCloseProfile(outputProfile);
        return 0;
    }
    
    // Create a color transform using the profiles
    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    
    // Clean up profiles
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    if (transform == NULL) {
        return 0;
    }
    
    // Call the function-under-test
    cmsUInt32Number outputFormat = cmsGetTransformOutputFormat(transform);

    // Clean up transform
    cmsDeleteTransform(transform);

    return 0;
}