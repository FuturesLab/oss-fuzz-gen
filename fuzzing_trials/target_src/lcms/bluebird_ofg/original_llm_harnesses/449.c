#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_449(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number manufacturer;

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    manufacturer = cmsGetHeaderManufacturer(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}