#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsInt32Number tagCount;

    // Create a profile from the data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // If the profile cannot be created, exit early
    }

    // Call the function-under-test
    tagCount = cmsGetTagCount(hProfile);

    // Close the profile to avoid memory leaks
    cmsCloseProfile(hProfile);

    return 0;
}