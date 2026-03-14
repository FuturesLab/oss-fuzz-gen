#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    cmsHPROFILE hProfile;
    cmsFloat64Number version;

    // Ensure that the size is sufficient for extracting a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Create a dummy profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a cmsFloat64Number from the input data
    version = *((cmsFloat64Number*)data);

    // Call the function-under-test
    cmsSetProfileVersion(hProfile, version);

    // Clean up the profile after testing
    cmsCloseProfile(hProfile);

    return 0;
}