#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract a cmsTagSignature
    if (size < sizeof(cmsTagSignature)) {
        return 0;
    }

    // Initialize a cmsHPROFILE
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // If profile creation fails, exit early
    }

    // Extract a cmsTagSignature from the input data
    cmsTagSignature tagSignature = *(cmsTagSignature *)data;

    // Call the function-under-test
    cmsTagSignature result = cmsTagLinkedTo(hProfile, tagSignature);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}