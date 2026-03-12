#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory-based profile from the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Allocate memory for the profile ID
    cmsUInt8Number profileID[16];
    
    // Call the function-under-test
    cmsGetHeaderProfileID(hProfile, profileID);

    // Close the profile to free resources
    cmsCloseProfile(hProfile);

    return 0;
}