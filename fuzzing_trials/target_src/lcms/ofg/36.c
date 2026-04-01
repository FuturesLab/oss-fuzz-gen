#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number index;
    cmsTagSignature tagSignature;

    // Initialize hProfile with a non-NULL value
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Use a fixed index for fuzzing
    index = size % 10; // Example: using size to determine index, ensuring it's within a reasonable range

    // Call the function-under-test
    tagSignature = cmsGetTagSignature(hProfile, index);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}