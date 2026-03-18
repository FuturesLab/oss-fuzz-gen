// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsGetHeaderCreationDateTime at cmsio0.c:1063:20 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsIsTag at cmsio0.c:709:19 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsSaveProfileToMem at cmsio0.c:1537:19 in lcms2.h
// cmsSaveProfileToMem at cmsio0.c:1537:19 in lcms2.h
// cmsSaveProfileToFile at cmsio0.c:1503:20 in lcms2.h
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lcms2.h"

static void fuzz_cmsGetHeaderCreationDateTime(cmsHPROFILE hProfile) {
    struct tm creationDate;
    cmsGetHeaderCreationDateTime(hProfile, &creationDate);
}

static void fuzz_cmsMD5computeID(cmsHPROFILE hProfile) {
    cmsMD5computeID(hProfile);
}

static void fuzz_cmsIsTag(cmsHPROFILE hProfile) {
    cmsTagSignature sig = 0; // Example signature, replace with appropriate value
    cmsIsTag(hProfile, sig);
}

static void fuzz_cmsGetTagCount(cmsHPROFILE hProfile) {
    cmsGetTagCount(hProfile);
}

static void fuzz_cmsSaveProfileToMem(cmsHPROFILE hProfile) {
    cmsUInt32Number bytesNeeded;
    cmsSaveProfileToMem(hProfile, NULL, &bytesNeeded);

    if (bytesNeeded > 0) {
        void *memPtr = malloc(bytesNeeded);
        if (memPtr) {
            cmsSaveProfileToMem(hProfile, memPtr, &bytesNeeded);
            free(memPtr);
        }
    }
}

static void fuzz_cmsSaveProfileToFile(cmsHPROFILE hProfile) {
    cmsSaveProfileToFile(hProfile, "./dummy_file");
}

int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsHPROFILE)) return 0;

    // Create a temporary file to store the input data
    FILE *tempFile = fopen("temp.icc", "wb");
    if (!tempFile) return 0;

    fwrite(Data, 1, Size, tempFile);
    fclose(tempFile);

    // Open the profile from the temporary file
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("temp.icc", "r");
    if (!hProfile) {
        remove("temp.icc");
        return 0;
    }

    fuzz_cmsGetHeaderCreationDateTime(hProfile);
    fuzz_cmsMD5computeID(hProfile);
    fuzz_cmsIsTag(hProfile);
    fuzz_cmsGetTagCount(hProfile);
    fuzz_cmsSaveProfileToMem(hProfile);
    fuzz_cmsSaveProfileToFile(hProfile);

    cmsCloseProfile(hProfile);
    remove("temp.icc");

    return 0;
}