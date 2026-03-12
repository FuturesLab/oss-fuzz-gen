#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static cmsHPROFILE loadProfileFromData(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);
    return cmsOpenProfileFromFile("./dummy_file", "r");
}

int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsTagSignature)) return 0;

    cmsHPROFILE hProfile = loadProfileFromData(Data, Size);
    if (!hProfile) return 0;

    cmsTagSignature sig = *(cmsTagSignature *)Data;

    // Fuzz cmsReadTag
    void* tagData = cmsReadTag(hProfile, sig);
    if (tagData) {
        // Handle tag data if necessary
    }

    // Fuzz cmsIsMatrixShaper
    cmsBool isMatrixShaper = cmsIsMatrixShaper(hProfile);

    // Fuzz cmsMD5computeID
    cmsBool md5Computed = cmsMD5computeID(hProfile);

    // Fuzz cmsIsTag
    cmsBool isTagPresent = cmsIsTag(hProfile, sig);

    // Fuzz cmsGetTagCount
    cmsInt32Number tagCount = cmsGetTagCount(hProfile);

    // Fuzz cmsSaveProfileToFile
    cmsBool saved = cmsSaveProfileToFile(hProfile, "./dummy_file");

    cmsCloseProfile(hProfile);
    return 0;
}