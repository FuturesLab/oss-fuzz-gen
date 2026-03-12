#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsFloat64Number result;

    // Check if the size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from memory
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function under test
    result = cmsDetectTAC(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}