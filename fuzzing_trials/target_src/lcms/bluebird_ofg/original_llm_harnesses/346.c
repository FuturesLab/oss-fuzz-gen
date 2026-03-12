#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_346(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    cmsHPROFILE hProfile;
    cmsUInt64Number attributes;

    // Ensure that the size is sufficient to extract a cmsUInt64Number
    if (size < sizeof(cmsUInt64Number)) {
        return 0; // Not enough data to proceed
    }

    // Create a profile using a built-in profile for testing purposes
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0; // Failed to create a profile
    }

    // Extract cmsUInt64Number from the input data
    attributes = *(const cmsUInt64Number *)data;

    // Call the function-under-test
    cmsSetHeaderAttributes(hProfile, attributes);

    // Cleanup
    cmsCloseProfile(hProfile);

    return 0;
}