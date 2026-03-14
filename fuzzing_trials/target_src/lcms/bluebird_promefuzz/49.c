#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static cmsHPROFILE LoadProfileFromMemory(const uint8_t *Data, size_t Size) {
    // Create a temporary file to simulate reading from a file
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        return NULL;
    }

    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Open the profile from the file
    cmsHPROFILE hProfile = cmsOpenProfileFromFile("./dummy_file", "r");
    return hProfile;
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    cmsHPROFILE hProfile = LoadProfileFromMemory(Data, Size);
    if (!hProfile) {
        return 0;
    }

    cmsInt32Number tagCount = cmsGetTagCount(hProfile);
    if (tagCount > 0) {
        for (cmsUInt32Number i = 0; i < (cmsUInt32Number)tagCount; i++) {
            cmsTagSignature sig = cmsGetTagSignature(hProfile, i);
            if (sig != 0) {
                void *tagData = cmsReadTag(hProfile, sig);
                // Normally you would do something with tagData, but we just test the call
            }
        }
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsSetColorSpace
    cmsColorSpaceSignature ret__cmsICCcolorSpace_zyxze = _cmsICCcolorSpace(INTENT_PRESERVE_K_ONLY_RELATIVE_COLORIMETRIC);

    cmsSetColorSpace(hProfile, ret__cmsICCcolorSpace_zyxze);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsGetPostScriptColorResource
    cmsContext ret_cmsGetProfileContextID_mukzx = cmsGetProfileContextID(hProfile);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetProfileContextID to cmsOpenProfileFromIOhandlerTHR
    cmsIOHANDLER* ret_cmsOpenIOhandlerFromNULL_wccto = cmsOpenIOhandlerFromNULL(ret_cmsGetProfileContextID_mukzx);
    if (ret_cmsOpenIOhandlerFromNULL_wccto == NULL){
    	return 0;
    }

    cmsHPROFILE ret_cmsOpenProfileFromIOhandlerTHR_owepq = cmsOpenProfileFromIOhandlerTHR(ret_cmsGetProfileContextID_mukzx, ret_cmsOpenIOhandlerFromNULL_wccto);

    // End mutation: Producer.APPEND_MUTATOR

    cmsIOHANDLER* ret_cmsOpenIOhandlerFromNULL_nwzab = cmsOpenIOhandlerFromNULL(0);
    if (ret_cmsOpenIOhandlerFromNULL_nwzab == NULL){
    	return 0;
    }

    cmsUInt32Number ret_cmsGetPostScriptColorResource_jehrk = cmsGetPostScriptColorResource(ret_cmsGetProfileContextID_mukzx, 0, hProfile, cmsD50X, cmsERROR_NULL, ret_cmsOpenIOhandlerFromNULL_nwzab);
    if (ret_cmsGetPostScriptColorResource_jehrk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsMD5computeID(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}