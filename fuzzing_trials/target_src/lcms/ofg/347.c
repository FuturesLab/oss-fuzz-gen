#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_347(const uint8_t *data, size_t size) {
    // Ensure there is enough data for cmsSetHeaderAttributes parameters
    if (size < sizeof(cmsUInt64Number)) {
        return 0;
    }

    // Create a memory-based profile using the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a cmsUInt64Number from the input data
    cmsUInt64Number attributes = *(const cmsUInt64Number *)data;

    // Call the function-under-test
    cmsSetHeaderAttributes(hProfile, attributes);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}