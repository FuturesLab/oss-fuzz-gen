// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsReadTag at cmsio0.c:1639:17 in lcms2.h
// cmsIsMatrixShaper at cmsio1.c:806:20 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsIsTag at cmsio0.c:709:19 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsSaveProfileToFile at cmsio0.c:1503:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>
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

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
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