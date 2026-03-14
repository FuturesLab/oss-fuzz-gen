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

int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
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
    cmsHPROFILE ret_cmsCreateLab2Profile_ygtdj = cmsCreateLab2Profile(NULL);


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 5 of cmsCreateTransformTHR
    cmsHTRANSFORM ret_cmsCreateTransformTHR_zjfvu = cmsCreateTransformTHR(0, ret_cmsCreateLab2Profile_ygtdj, INTENT_PRESERVE_K_PLANE_RELATIVE_COLORIMETRIC, hProfile, cmsERROR_COLORSPACE_CHECK, cmsSPOT_CROSS, cmsSPOT_ROUND);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    cmsCloseProfile(hProfile);
    return 0;
}