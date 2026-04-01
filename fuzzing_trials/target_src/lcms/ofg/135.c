#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsProfileClassSignature deviceClass;

    // Check if the input size is sufficient for a minimal ICC profile header
    if (size < 128) {
        return 0;
    }

    // Create a memory-based profile from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    deviceClass = cmsGetDeviceClass(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}