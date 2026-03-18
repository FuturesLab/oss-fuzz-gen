#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number flags;

    // Ensure there is enough data to extract necessary values
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize a profile using a built-in profile as a template
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract flags from the input data
    flags = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    cmsSetHeaderFlags(hProfile, flags);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}