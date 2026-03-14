#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_258(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for profile creation
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory-based profile using the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Prepare a variable to receive header attributes
    cmsUInt64Number attributes = 0;

    // Call the function-under-test
    cmsGetHeaderAttributes(hProfile, &attributes);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}