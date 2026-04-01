#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_480(const uint8_t *data, size_t size) {
    // Initialize a cmsHPROFILE
    cmsHPROFILE hProfile = NULL;

    // Check if the size is sufficient to create a profile from memory
    if (size >= sizeof(cmsHPROFILE)) {
        // Create a profile from memory using the input data
        hProfile = cmsOpenProfileFromMem(data, size);
    }

    // If the profile is successfully created, call the function-under-test
    if (hProfile != NULL) {
        cmsColorSpaceSignature pcs = cmsGetPCS(hProfile);
        
        // Close the profile after use
        cmsCloseProfile(hProfile);
    }

    return 0;
}