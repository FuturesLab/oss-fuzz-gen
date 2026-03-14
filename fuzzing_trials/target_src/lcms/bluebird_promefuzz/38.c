#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcms2.h"

static cmsHPROFILE createDummyProfile() {
    // Create a dummy ICC profile for testing
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    return hProfile;
}

static void cleanupProfile(cmsHPROFILE hProfile) {
    if (hProfile != NULL) {
        cmsCloseProfile(hProfile);
    }
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsHPROFILE hProfile = createDummyProfile();
    if (hProfile == NULL) {
        return 0;
    }

    cmsTagSignature tagSig = *(cmsTagSignature *)Data;
    cmsUInt32Number bufferSize = Size - sizeof(cmsUInt32Number);
    const void* rawData = Data + sizeof(cmsUInt32Number);

    // Fuzz cmsReadTag
    void* tagData = cmsReadTag(hProfile, tagSig);
    if (tagData != NULL) {
        // Process tagData if needed
    }

    // Fuzz cmsReadRawTag
    void* buffer = malloc(bufferSize);
    if (buffer != NULL) {
        cmsUInt32Number bytesRead = cmsReadRawTag(hProfile, tagSig, buffer, bufferSize);
        // Process bytesRead if needed
        free(buffer);
    }

    // Fuzz cmsWriteRawTag
    cmsBool writeSuccess = cmsWriteRawTag(hProfile, tagSig, rawData, bufferSize);
    if (writeSuccess) {
        // Handle successful write if needed
    }

    // Fuzz cmsGetTagCount
    cmsInt32Number tagCount = cmsGetTagCount(hProfile);
    if (tagCount >= 0) {
        // Process tagCount if needed
    }

    // Fuzz cmsGetTagSignature
    if (tagCount > 0) {
        cmsTagSignature retrievedSig = cmsGetTagSignature(hProfile, 0);
        // Process retrievedSig if needed
    }

    // Fuzz cmsTagLinkedTo
    cmsTagSignature linkedSig = cmsTagLinkedTo(hProfile, tagSig);
    if (linkedSig != 0) {
        // Process linkedSig if needed
    }

    cleanupProfile(hProfile);
    return 0;
}