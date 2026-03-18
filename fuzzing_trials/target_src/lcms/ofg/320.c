#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    cmsHPROFILE hProfile;
    cmsTagSignature tagSignature;
    const void *tagData;

    // Create a dummy profile for fuzzing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Initialize tagSignature with a non-zero value
    tagSignature = (cmsTagSignature) 0x74786574; // 'text' in ASCII

    // Use the input data as the tag data, ensure it is not NULL
    tagData = (const void *)data;

    // Call the function-under-test
    cmsWriteTag(hProfile, tagSignature, tagData);

    // Clean up the profile
    cmsCloseProfile(hProfile);

    return 0;
}