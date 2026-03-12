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

int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size) {
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
    cmsBool isSupported = cmsIsIntentSupported(hProfile, Intent, UsedDirection);

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


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsIsMatrixShaper

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsGetPostScriptCRD

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsSetAdaptationState
    cmsFloat64Number ret_cmsSetAdaptationState_drign = cmsSetAdaptationState(cmsReflective);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_cmsSetAdaptationState_drign < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsGetPostScriptCRD with cmsGetPostScriptCSA

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsGetPostScriptCSA
    cmsUInt32Number ret_cmsGetPostScriptCRD_vsmpe = cmsGetPostScriptCSA(0, hProfile, Size, PT_HSV, NULL, INTENT_PRESERVE_K_ONLY_RELATIVE_COLORIMETRIC);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_cmsGetPostScriptCRD_vsmpe < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsIsMatrixShaper(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}