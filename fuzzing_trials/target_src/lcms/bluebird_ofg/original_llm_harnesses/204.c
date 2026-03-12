#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt8Number profileID[16]; // 16 bytes for profile ID

    // Ensure data is not empty and can be used to create a profile
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsGetHeaderProfileID(hProfile, profileID);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}