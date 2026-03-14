#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_326(const uint8_t *data, size_t size) {
    // Initialize the parameters for cmsSetHeaderProfileID
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    cmsUInt8Number profileID[16]; // Profile ID is typically 16 bytes

    // Ensure the profile is valid before proceeding
    if (hProfile != NULL) {
        // Fill profileID with some data, using the input data if available
        for (size_t i = 0; i < 16 && i < size; ++i) {
            profileID[i] = data[i];
        }
        
        // Call the function-under-test
        cmsSetHeaderProfileID(hProfile, profileID);

        // Close the profile after use
        cmsCloseProfile(hProfile);
    }

    return 0;
}