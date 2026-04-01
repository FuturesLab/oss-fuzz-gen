#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_259(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt64Number attributes = 0;

    // Ensure that the data size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from the data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsGetHeaderAttributes(hProfile, &attributes);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}