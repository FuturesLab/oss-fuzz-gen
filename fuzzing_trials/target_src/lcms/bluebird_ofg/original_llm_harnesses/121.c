#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsIOHANDLER *ioHandler;

    // Initialize a memory-based profile using the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // Return early if the profile cannot be opened
    }

    // Call the function-under-test
    ioHandler = cmsGetProfileIOhandler(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}