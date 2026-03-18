#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_452(const uint8_t *data, size_t size) {
    // Initialize a memory context for LittleCMS
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMemTHR(context, data, size);

    if (hProfile != NULL) {
        // Call the function-under-test with the created profile
        cmsBool result = cmsIsMatrixShaper(hProfile);

        // Close the profile after use
        cmsCloseProfile(hProfile);
    }

    // Free the memory context
    cmsDeleteContext(context);

    return 0;
}