#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a memory-based profile for fuzzing
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a cmsUInt32Number from the input data
    cmsUInt32Number manufacturer = *(const cmsUInt32Number*)data;

    // Call the function-under-test
    cmsSetHeaderManufacturer(hProfile, manufacturer);

    // Close the profile after use
    cmsCloseProfile(hProfile);

    return 0;
}