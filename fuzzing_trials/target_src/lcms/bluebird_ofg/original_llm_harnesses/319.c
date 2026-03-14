#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsTagSignature) + sizeof(void*)) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    cmsTagSignature tagSig = *(cmsTagSignature*)data;
    const void *tagData = (const void*)(data + sizeof(cmsTagSignature));

    // Ensure hProfile is valid
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsWriteTag(hProfile, tagSig, tagData);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}