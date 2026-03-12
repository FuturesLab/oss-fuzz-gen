#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;

    // Ensure the data is large enough to be a valid profile
    if (size >= sizeof(cmsHPROFILE)) {
        // Create a memory-based profile from the input data
        hProfile = cmsOpenProfileFromMem(data, size);

        if (hProfile != NULL) {
            // Call the function-under-test
            cmsUInt32Number flags = cmsGetHeaderFlags(hProfile);

            // Close the profile after use
            cmsCloseProfile(hProfile);
        }
    }

    return 0;
}