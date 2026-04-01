#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_430(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract required parameters
    if (size < sizeof(cmsTagSignature) + sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize variables
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    cmsTagSignature tagSig = *(cmsTagSignature *)(data);
    cmsUInt32Number bufferSize = *(cmsUInt32Number *)(data + sizeof(cmsTagSignature));
    void *buffer = malloc(bufferSize);

    if (hProfile != NULL && buffer != NULL) {
        // Call the function-under-test
        cmsReadRawTag(hProfile, tagSig, buffer, bufferSize);

        // Clean up
        cmsCloseProfile(hProfile);
    }

    free(buffer);
    return 0;
}