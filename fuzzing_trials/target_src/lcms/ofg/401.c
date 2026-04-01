#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_401(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to avoid passing NULL to the function
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromMem((const void *)data, (cmsUInt32Number)size);

    // Check if the profile was opened successfully and close it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}