#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsTagSignature tagSig;
    cmsTagSignature linkedTag;

    // Check if the size is sufficient to extract a cmsTagSignature
    if (size < sizeof(cmsTagSignature)) {
        return 0;
    }

    // Initialize the cmsHPROFILE with a dummy profile
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract cmsTagSignature from the data
    tagSig = *(cmsTagSignature *)data;

    // Call the function-under-test
    linkedTag = cmsTagLinkedTo(hProfile, tagSig);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}