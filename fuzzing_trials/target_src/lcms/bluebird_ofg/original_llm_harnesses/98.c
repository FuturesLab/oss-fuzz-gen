#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h> // Include the Little CMS library header

// Remove 'extern "C"' as it is not needed in a C file
int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;

    // Create a memory-based profile from the input data
    if (size > 0) {
        hProfile = cmsOpenProfileFromMem((void*)data, (cmsUInt32Number)size);
    }

    // Check if the profile was successfully created
    if (hProfile != NULL) {
        // Call the function-under-test
        cmsBool result = cmsMD5computeID(hProfile);

        // Close the profile after use
        cmsCloseProfile(hProfile);
    }

    return 0;
}