#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;

    // Check if the input data is large enough to be used
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from memory using the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsFloat64Number version = cmsGetProfileVersion(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}