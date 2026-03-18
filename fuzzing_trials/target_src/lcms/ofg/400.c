#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_400(const uint8_t *data, size_t size) {
    // Ensure that the size is greater than zero to avoid passing NULL to cmsOpenProfileFromMem
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromMem((const void *)data, (cmsUInt32Number)size);

    // If the profile is successfully opened, close it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}