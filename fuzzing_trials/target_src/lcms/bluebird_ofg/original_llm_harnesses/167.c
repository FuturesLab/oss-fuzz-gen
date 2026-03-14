#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number dwFlags;
    cmsBool bInput;

    // Initialize variables with non-NULL values
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // If profile creation fails, exit early
    }

    // Use the first byte of data for dwFlags if size permits, otherwise default to 0
    dwFlags = (size > 0) ? data[0] : 0;

    // Use the second byte of data for bInput if size permits, otherwise default to TRUE
    bInput = (size > 1) ? (data[1] % 2 == 0) : TRUE;

    // Call the function under test
    cmsUInt32Number result = cmsFormatterForColorspaceOfProfile(hProfile, dwFlags, bInput);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}