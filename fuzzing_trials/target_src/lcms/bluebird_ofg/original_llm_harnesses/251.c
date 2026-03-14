#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number Intent = 0;
    cmsUInt32Number Flags = 0;

    // Create a profile from the input data, assuming the data size is sufficient
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Fuzz the cmsIsCLUT function
    cmsBool result = cmsIsCLUT(hProfile, Intent, Flags);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}