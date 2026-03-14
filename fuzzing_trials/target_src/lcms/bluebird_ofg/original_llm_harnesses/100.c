#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;
    cmsFloat64Number version;

    // Create a profile from the input data
    if (size > 0) {
        hProfile = cmsOpenProfileFromMem(data, size);
    }

    // If the profile is successfully created, get its version
    if (hProfile != NULL) {
        version = cmsGetProfileVersion(hProfile);

        // Close the profile
        cmsCloseProfile(hProfile);
    }

    return 0;
}