#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_300(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;

    // Create a profile from the input data if possible
    if (size > 0) {
        hProfile = cmsOpenProfileFromMem(data, size);
    } else {
        // If size is 0, create a default profile as a fallback
        hProfile = cmsCreate_sRGBProfile();
    }

    if (hProfile != NULL) {
        // Call the function-under-test
        cmsUInt32Number creator = cmsGetHeaderCreator(hProfile);

        // Close the profile after use
        cmsCloseProfile(hProfile);
    }

    return 0;
}