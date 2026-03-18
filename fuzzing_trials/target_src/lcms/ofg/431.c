#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_431(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsTagSignature tagSignature;
    void *buffer;
    cmsUInt32Number bufferSize;
    cmsUInt32Number result;

    // Ensure that the data size is sufficient for our needs
    if (size < sizeof(cmsTagSignature) + sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize hProfile
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract tagSignature from data
    tagSignature = *(cmsTagSignature *)data;

    // Initialize buffer and bufferSize
    bufferSize = *(cmsUInt32Number *)(data + sizeof(cmsTagSignature));
    buffer = (void *)(data + sizeof(cmsTagSignature) + sizeof(cmsUInt32Number));

    // Call the function-under-test
    result = cmsReadRawTag(hProfile, tagSignature, buffer, bufferSize);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}