#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_426(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;
    cmsTagSignature tagSignature;

    // Ensure the size is sufficient to extract a tag signature
    if (size < sizeof(cmsTagSignature)) {
        return 0;
    }

    // Initialize the tag signature from the input data
    tagSignature = *(cmsTagSignature*)data;

    // Create a dummy profile for testing purposes
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIsTag(hProfile, tagSignature);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}