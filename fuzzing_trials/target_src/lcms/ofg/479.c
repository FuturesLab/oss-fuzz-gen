#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_479(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsColorSpaceSignature pcs;

    // Ensure the data size is sufficient for creating a profile
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a profile from memory using the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    pcs = cmsGetPCS(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}