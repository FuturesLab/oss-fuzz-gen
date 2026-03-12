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

int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetHeaderModel to cmsCreateTransform
    cmsHPROFILE ret_cmsCreateNULLProfileTHR_ejzrg = cmsCreateNULLProfileTHR(0);

    cmsHTRANSFORM ret_cmsCreateTransform_vtlvw = cmsCreateTransform(ret_cmsCreateNULLProfileTHR_ejzrg, DARK_SURROUND, 0, LCMS_USED_AS_PROOF, cmsGlossy, headerModel);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsFormatterForPCSOfProfile with cmsFormatterForColorspaceOfProfile
    cmsUInt32Number formatterPCS = cmsFormatterForColorspaceOfProfile(hProfile, nBytes, lIsFloat);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR




    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsCreateProofingTransformTHR
    cmsContext ret_cmsGetProfileContextID_atyvm = cmsGetProfileContextID(0);
    cmsHPROFILE ret_cmsCreateDeviceLinkFromCubeFile_fntso = cmsCreateDeviceLinkFromCubeFile((const char *)"r");

    cmsHTRANSFORM ret_cmsCreateProofingTransformTHR_zrdpd = cmsCreateProofingTransformTHR(ret_cmsGetProfileContextID_atyvm, hProfile, cmsReflective, ret_cmsCreateDeviceLinkFromCubeFile_fntso, cmsSPOT_UNKNOWN, 0, cmsERROR_BAD_SIGNATURE, cmsPERCEPTUAL_BLACK_Y, PT_MCH14);

    // End mutation: Producer.APPEND_MUTATOR

    cmsCloseProfile(hProfile);
    return 0;
}