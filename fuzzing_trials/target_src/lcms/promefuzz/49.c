// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:680:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsReadTag at cmsio0.c:1639:17 in lcms2.h
// cmsReadRawTag at cmsio0.c:1913:27 in lcms2.h
// cmsWriteRawTag at cmsio0.c:2040:19 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsGetTagSignature at cmsio0.c:590:27 in lcms2.h
// cmsTagLinkedTo at cmsio0.c:2098:28 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcms2.h>

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

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
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