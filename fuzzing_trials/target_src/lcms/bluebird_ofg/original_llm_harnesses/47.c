#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number model;

    // Ensure the input data is non-zero to create a valid profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem((const void*)data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    model = cmsGetHeaderModel(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}