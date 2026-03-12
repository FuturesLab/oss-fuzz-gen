#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcms2.h"

static cmsHPROFILE loadProfileFromData(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return NULL;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);
    
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    cmsHPROFILE hProfile = loadProfileFromData(Data, Size);
    if (!hProfile) {
        return 0;
    }

    cmsUInt32Number Intent = Data[0] % 4; // Random intent
    cmsUInt32Number UsedDirection = Data[0] % 2; // Random direction

    // Fuzz cmsIsIntentSupported

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsIsIntentSupported

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsIsIntentSupported
    cmsBool isSupported = cmsIsIntentSupported(hProfile, cmsSPOT_LINE, cmsPERCEPTUAL_BLACK_Z);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Fuzz cmsGetHeaderFlags
    cmsUInt32Number headerFlags = cmsGetHeaderFlags(hProfile);

    // Fuzz cmsFormatterForColorspaceOfProfile
    cmsUInt32Number nBytes = (Data[0] % 2) + 1; // Random byte size, 1 or 2
    cmsBool lIsFloat = Data[0] % 2; // Random float flag
    cmsUInt32Number formatterColorspace = cmsFormatterForColorspaceOfProfile(hProfile, nBytes, lIsFloat);

    // Fuzz cmsGetHeaderCreator

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsGetHeaderCreator with cmsGetHeaderModel
    cmsUInt32Number headerCreator = cmsGetHeaderModel(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz cmsGetHeaderModel
    cmsUInt32Number headerModel = cmsGetHeaderModel(hProfile);

    // Fuzz cmsFormatterForPCSOfProfile
    cmsUInt32Number formatterPCS = cmsFormatterForPCSOfProfile(hProfile, nBytes, lIsFloat);

    cmsCloseProfile(hProfile);
    return 0;
}