#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>  // Include the Little CMS library header

// Define the LLVMFuzzerTestOneInput function
int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsUInt32Number flags;

    // Ensure there is enough data to read from
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a profile using cmsOpenProfileFromMem
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract flags from the input data
    flags = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    cmsSetHeaderFlags(hProfile, flags);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}