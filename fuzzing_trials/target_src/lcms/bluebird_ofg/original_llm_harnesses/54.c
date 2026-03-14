#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    void *buffer;
    cmsUInt32Number bufferSize;
    cmsBool result;

    // Initialize the LCMS context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem(data, size);

    // Check if the profile was created successfully
    if (hProfile == NULL) {
        cmsDeleteContext(context);
        return 0;
    }

    // Allocate a buffer for saving the profile
    bufferSize = size * 2; // Assume the buffer size is twice the input size
    buffer = malloc(bufferSize);
    if (buffer == NULL) {
        cmsCloseProfile(hProfile);
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function under test
    result = cmsSaveProfileToMem(hProfile, buffer, &bufferSize);

    // Clean up
    free(buffer);
    cmsCloseProfile(hProfile);
    cmsDeleteContext(context);

    return 0;
}