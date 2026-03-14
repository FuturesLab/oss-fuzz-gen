#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_389(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsColorSpaceSignature colorSpace;

    // Ensure data is large enough to extract a cmsColorSpaceSignature
    if (size >= sizeof(cmsColorSpaceSignature)) {
        // Copy data into colorSpace, ensuring it is not NULL
        colorSpace = *(cmsColorSpaceSignature*)data;

        // Call the function-under-test
        cmsSetColorSpace(hProfile, colorSpace);
    }

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}