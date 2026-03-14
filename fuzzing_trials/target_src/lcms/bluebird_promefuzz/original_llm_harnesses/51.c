// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsGetHeaderRenderingIntent at cmsio0.c:985:27 in lcms2.h
// cmsGetHeaderManufacturer at cmsio0.c:1009:27 in lcms2.h
// cmsSetEncodedICCversion at cmsio0.c:1112:16 in lcms2.h
// cmsSetHeaderRenderingIntent at cmsio0.c:991:16 in lcms2.h
// cmsGetHeaderCreator at cmsio0.c:1021:27 in lcms2.h
// cmsGetHeaderModel at cmsio0.c:1027:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

static cmsHPROFILE createDummyProfile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);

    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsHPROFILE hProfile = createDummyProfile(Data, Size);
    if (!hProfile) return 0;

    // Test cmsGetHeaderRenderingIntent
    cmsUInt32Number renderingIntent = cmsGetHeaderRenderingIntent(hProfile);

    // Test cmsGetHeaderManufacturer
    cmsUInt32Number manufacturer = cmsGetHeaderManufacturer(hProfile);

    // Test cmsSetEncodedICCversion
    cmsUInt32Number version = *(cmsUInt32Number*)Data;
    cmsSetEncodedICCversion(hProfile, version);

    // Test cmsSetHeaderRenderingIntent
    cmsUInt32Number newRenderingIntent = *(cmsUInt32Number*)Data;
    cmsSetHeaderRenderingIntent(hProfile, newRenderingIntent);

    // Test cmsGetHeaderCreator
    cmsUInt32Number creator = cmsGetHeaderCreator(hProfile);

    // Test cmsGetHeaderModel
    cmsUInt32Number model = cmsGetHeaderModel(hProfile);

    cmsCloseProfile(hProfile);
    return 0;
}