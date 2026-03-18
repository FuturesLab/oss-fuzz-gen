// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsStageAllocCLut16bitGranular at cmslut.c:547:21 in lcms2.h
// cmsStageSampleCLutFloat at cmslut.c:813:19 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsIsCLUT at cmsio1.c:830:20 in lcms2.h
// cmsCreateTransform at cmsxform.c:1355:32 in lcms2.h
// cmsChangeBuffersFormat at cmsxform.c:1446:19 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1398:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>

#define MIN_CLUT_POINTS 3

static cmsBool SamplerFunction(cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    // Dummy sampler function for testing
    return TRUE;
}

int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    if (Size < MIN_CLUT_POINTS * sizeof(cmsUInt32Number)) return 0;

    // Ensure enough data for clutPoints
    cmsUInt32Number clutPoints[MIN_CLUT_POINTS];
    memcpy(clutPoints, Data, MIN_CLUT_POINTS * sizeof(cmsUInt32Number));

    // Calculate the size for the table based on clutPoints
    size_t tableSize = 1;
    for (int i = 0; i < MIN_CLUT_POINTS; i++) {
        tableSize *= clutPoints[i];
    }
    tableSize *= 3 * sizeof(cmsUInt16Number); // 3 channels

    if (Size < MIN_CLUT_POINTS * sizeof(cmsUInt32Number) + tableSize) return 0;

    // Dummy context and stage initialization
    cmsContext context = NULL;
    cmsStage* stage = cmsStageAllocCLut16bitGranular(context, clutPoints, 3, 3, (cmsUInt16Number*)(Data + MIN_CLUT_POINTS * sizeof(cmsUInt32Number)));

    if (stage) {
        // Fuzz cmsStageSampleCLutFloat
        cmsStageSampleCLutFloat(stage, SamplerFunction, NULL, *Data);

        // Cleanup
        cmsStageFree(stage);
    }

    // Write dummy data to a file for cmsOpenProfileFromFile
    FILE* dummyFile = fopen("./dummy_file", "wb");
    if (dummyFile) {
        fwrite(Data, 1, Size, dummyFile);
        fclose(dummyFile);
    }

    // Dummy profile initialization
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    if (hProfile) {
        // Fuzz cmsIsCLUT
        cmsIsCLUT(hProfile, *Data, *Data);

        // Fuzz cmsCreateTransform
        cmsHTRANSFORM hTransform = cmsCreateTransform(hProfile, *Data, hProfile, *Data, *Data, *Data);
        if (hTransform) {
            // Fuzz cmsChangeBuffersFormat
            cmsChangeBuffersFormat(hTransform, *Data, *Data);

            // Cleanup
            cmsDeleteTransform(hTransform);
        }

        // Fuzz cmsCreateProofingTransform
        cmsHTRANSFORM hProofTransform = cmsCreateProofingTransform(hProfile, *Data, hProfile, *Data, hProfile, *Data, *Data, *Data);
        if (hProofTransform) {
            // Cleanup
            cmsDeleteTransform(hProofTransform);
        }

        // Cleanup
        cmsCloseProfile(hProfile);
    }

    return 0;
}