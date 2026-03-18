#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number tagIndex;
    cmsTagSignature tagSignature;

    // Ensure there is enough data to read a cmsUInt32Number for tagIndex
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Open a profile from memory using the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract the tag index from the input data
    tagIndex = *((cmsUInt32Number*)data);

    // Call the function-under-test
    tagSignature = cmsGetTagSignature(hProfile, tagIndex);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}