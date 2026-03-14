#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Initialize the variables required for the function call
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // If the profile cannot be opened, exit early
    }

    // Allocate memory for the output buffer
    void *buffer = malloc(size);
    if (buffer == NULL) {
        cmsCloseProfile(hProfile);
        return 0; // If memory allocation fails, exit early
    }

    // Initialize a variable to hold the size of the saved profile
    cmsUInt32Number savedSize = 0;

    // Call the function-under-test
    cmsBool result = cmsSaveProfileToMem(hProfile, buffer, &savedSize);

    // Clean up resources
    free(buffer);
    cmsCloseProfile(hProfile);

    return 0;
}