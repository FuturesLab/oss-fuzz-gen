#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsInt32Number tagCount;

    // Create a profile from the input data if possible
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // Return if profile creation fails
    }

    // Call the function-under-test
    tagCount = cmsGetTagCount(hProfile);

    // Close the profile to avoid memory leaks
    cmsCloseProfile(hProfile);

    return 0;
}