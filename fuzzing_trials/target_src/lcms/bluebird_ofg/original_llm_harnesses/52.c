#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Open a profile from the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    
    if (hProfile != NULL) {
        // If the profile is successfully opened, perform some operations
        cmsCloseProfile(hProfile);
    }
    
    return 0;
}