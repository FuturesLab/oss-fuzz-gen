#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_462(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;

    // Create a profile from memory using the input data
    if (size > 0) {
        hProfile = cmsOpenProfileFromMem(data, size);
    }

    // If the profile was successfully created, close it
    if (hProfile != NULL) {
        cmsCloseProfile(hProfile);
    }

    return 0;
}