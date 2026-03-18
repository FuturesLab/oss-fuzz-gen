// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateXYZProfileTHR at cmsvirt.c:577:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateProofingTransformTHR at cmsxform.c:1366:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsGetContextUserData at cmsplugin.c:1021:17 in lcms2.h
// _cmsMallocZero at cmserr.c:272:17 in lcms2_plugin.h
// cmsCreateDeviceLinkFromCubeFileTHR at cmscgats.c:3211:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
// cmsCreateTransformTHR at cmsxform.c:1338:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcms2.h>
#include <lcms2_plugin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void write_dummy_cube_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 5) return 0;

    cmsContext context = NULL;
    cmsHPROFILE inputProfile = NULL;
    cmsHPROFILE outputProfile = NULL;
    cmsHPROFILE proofingProfile = NULL;
    cmsHTRANSFORM transform = NULL;
    cmsHPROFILE deviceLinkProfile = NULL;
    cmsUInt32Number inputFormat = *(cmsUInt32Number *)Data;
    cmsUInt32Number outputFormat = *(cmsUInt32Number *)(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number intent = *(cmsUInt32Number *)(Data + 2 * sizeof(cmsUInt32Number));
    cmsUInt32Number proofingIntent = *(cmsUInt32Number *)(Data + 3 * sizeof(cmsUInt32Number));
    cmsUInt32Number flags = *(cmsUInt32Number *)(Data + 4 * sizeof(cmsUInt32Number));

    // Test cmsCreateXYZProfileTHR
    cmsHPROFILE xyzProfile = cmsCreateXYZProfileTHR(context);
    if (xyzProfile) {
        cmsCloseProfile(xyzProfile);
    }

    // Test cmsCreateProofingTransformTHR
    transform = cmsCreateProofingTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, proofingProfile, intent, proofingIntent, flags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    // Test cmsGetContextUserData
    void *userData = cmsGetContextUserData(context);

    // Test _cmsMallocZero
    void *allocatedMemory = _cmsMallocZero(context, Size);
    if (allocatedMemory) {
        free(allocatedMemory);
    }

    // Test cmsCreateDeviceLinkFromCubeFileTHR
    write_dummy_cube_file(Data, Size);
    deviceLinkProfile = cmsCreateDeviceLinkFromCubeFileTHR(context, "./dummy_file");
    if (deviceLinkProfile) {
        cmsCloseProfile(deviceLinkProfile);
    }

    // Test cmsCreateTransformTHR
    transform = cmsCreateTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    return 0;
}