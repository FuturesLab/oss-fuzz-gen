#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_424(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsTagSignature)) {
        return 0;
    }

    // Create a memory-based profile using the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a cmsTagSignature from the input data
    cmsTagSignature tagSignature = *(cmsTagSignature *)data;

    // Call the function-under-test
    void *tagData = cmsReadTag(hProfile, tagSignature);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}