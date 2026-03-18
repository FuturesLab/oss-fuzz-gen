#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_425(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsTagSignature tagSignature;

    // Ensure the size is sufficient for the operations
    if (size < sizeof(cmsTagSignature)) {
        return 0;
    }

    // Create a profile from memory
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a tag signature from the input data
    tagSignature = *(cmsTagSignature *)data;

    // Call the function-under-test
    cmsBool result = cmsIsTag(hProfile, tagSignature);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}