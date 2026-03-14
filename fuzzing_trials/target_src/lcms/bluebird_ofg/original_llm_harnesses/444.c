#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_444(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsColorSpaceSignature colorSpace;

    // Check if the input size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory-based profile using the input data
    hProfile = cmsOpenProfileFromMem((void*)data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    colorSpace = cmsGetColorSpace(hProfile);

    // Close the profile to free resources
    cmsCloseProfile(hProfile);

    return 0;
}