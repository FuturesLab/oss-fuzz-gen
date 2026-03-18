#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsContext contextID;

    // Check if the size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    contextID = cmsGetProfileContextID(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}