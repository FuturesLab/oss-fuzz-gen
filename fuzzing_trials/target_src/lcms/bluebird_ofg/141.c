#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsHPROFILE hProfile;
    cmsTagSignature tagSignature;
    const void *tagData;
    cmsUInt32Number tagSize;

    // Ensure the size is sufficient for the parameters
    if (size < sizeof(cmsTagSignature) + sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Extract tagSignature and tagSize from the input data
    tagSignature = *(cmsTagSignature *)data;
    tagSize = *(cmsUInt32Number *)(data + sizeof(cmsTagSignature));

    // Ensure tagSize does not exceed the remaining data size
    if (tagSize > size - sizeof(cmsTagSignature) - sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Point tagData to the appropriate location in the input data
    tagData = (const void *)(data + sizeof(cmsTagSignature) + sizeof(cmsUInt32Number));

    // Create a dummy profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsWriteRawTag(hProfile, tagSignature, tagData, tagSize);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}