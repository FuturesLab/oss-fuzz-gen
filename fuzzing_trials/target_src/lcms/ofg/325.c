#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_325(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt8Number profileID[16]; // Typically, a profile ID is 16 bytes

    // Initialize profileID with non-zero values
    for (int i = 0; i < 16 && i < size; i++) {
        profileID[i] = data[i];
    }
    for (int i = size; i < 16; i++) {
        profileID[i] = (cmsUInt8Number)(i + 1);
    }

    // Create a dummy profile to ensure hProfile is not NULL
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function under test
    cmsSetHeaderProfileID(hProfile, profileID);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}