// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenProfileFromFile at cmsio0.c:1232:23 in lcms2.h
// cmsIsIntentSupported at cmsio1.c:864:20 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:997:27 in lcms2.h
// cmsFormatterForColorspaceOfProfile at cmspack.c:4025:27 in lcms2.h
// cmsGetHeaderCreator at cmsio0.c:1021:27 in lcms2.h
// cmsGetHeaderModel at cmsio0.c:1027:27 in lcms2.h
// cmsFormatterForPCSOfProfile at cmspack.c:4044:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1585:20 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcms2.h>

static cmsHPROFILE loadProfileFromData(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(Data, 1, Size, file);
    fclose(file);
    
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHPROFILE hProfile = loadProfileFromData(Data, Size);
    if (!hProfile) return 0;

    cmsUInt32Number Intent = Data[0] % 4; // Random intent
    cmsUInt32Number UsedDirection = Data[0] % 2; // Random direction

    // Fuzz cmsIsIntentSupported
    cmsBool isSupported = cmsIsIntentSupported(hProfile, Intent, UsedDirection);

    // Fuzz cmsGetHeaderFlags
    cmsUInt32Number headerFlags = cmsGetHeaderFlags(hProfile);

    // Fuzz cmsFormatterForColorspaceOfProfile
    cmsUInt32Number nBytes = (Data[0] % 2) + 1; // Random byte size, 1 or 2
    cmsBool lIsFloat = Data[0] % 2; // Random float flag
    cmsUInt32Number formatterColorspace = cmsFormatterForColorspaceOfProfile(hProfile, nBytes, lIsFloat);

    // Fuzz cmsGetHeaderCreator
    cmsUInt32Number headerCreator = cmsGetHeaderCreator(hProfile);

    // Fuzz cmsGetHeaderModel
    cmsUInt32Number headerModel = cmsGetHeaderModel(hProfile);

    // Fuzz cmsFormatterForPCSOfProfile
    cmsUInt32Number formatterPCS = cmsFormatterForPCSOfProfile(hProfile, nBytes, lIsFloat);

    cmsCloseProfile(hProfile);
    return 0;
}