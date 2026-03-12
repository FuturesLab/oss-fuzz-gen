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

int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetTagCount to cmsGetSupportedIntents
    cmsBool ret_cmsCloseProfile_htohq = cmsCloseProfile(0);
    if (ret_cmsCloseProfile_htohq < 0){
    	return 0;
    }
    char mivoyedl[1024] = "tcbla";
    cmsBool ret_cmsPlugin_pukww = cmsPlugin(mivoyedl);
    if (ret_cmsPlugin_pukww < 0){
    	return 0;
    }

    cmsUInt32Number ret_cmsGetSupportedIntents_yhtbs = cmsGetSupportedIntents((unsigned long )tagCount, (unsigned long )ret_cmsCloseProfile_htohq, (char **)&mivoyedl);
    if (ret_cmsGetSupportedIntents_yhtbs < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsCreateTransformTHR

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetSupportedIntents to cmsOpenIOhandlerFromMem
    cmsContext ret_cmsGetTransformContextID_yyfog = cmsGetTransformContextID(0);

    cmsIOHANDLER* ret_cmsOpenIOhandlerFromMem_qfxac = cmsOpenIOhandlerFromMem(ret_cmsGetTransformContextID_yyfog, (void *)Data, cmsERROR_COLORSPACE_CHECK, &mivoyedl);
    if (ret_cmsOpenIOhandlerFromMem_qfxac == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsContext ret_cmsGetProfileContextID_sthns = cmsGetProfileContextID(hProfile);

    cmsHTRANSFORM ret_cmsCreateTransformTHR_cuydu = cmsCreateTransformTHR(ret_cmsGetProfileContextID_sthns, hProfile, PT_GRAY, 0, cmsERROR_CORRUPTION_DETECTED, PT_MCH15, cmsSPOT_ROUND);

    // End mutation: Producer.APPEND_MUTATOR

    cmsCloseProfile(hProfile);
    return 0;
}