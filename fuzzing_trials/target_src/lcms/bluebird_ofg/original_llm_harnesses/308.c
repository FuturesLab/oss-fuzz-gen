#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsUInt32Number manufacturer;

    // Check if the size of the input data is sufficient
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a cmsUInt32Number from the input data
    manufacturer = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    cmsSetHeaderManufacturer(hProfile, manufacturer);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}