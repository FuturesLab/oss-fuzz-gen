#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_301(const uint8_t *data, size_t size) {
    // Create a memory-based profile using the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    
    // Check if the profile was created successfully
    if (hProfile != NULL) {
        // Call the function-under-test
        cmsUInt32Number creator = cmsGetHeaderCreator(hProfile);

        // Close the profile to free resources
        cmsCloseProfile(hProfile);
    }

    return 0;
}