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

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsWriteTag

    cmsBool ret_cmsWriteTag_yqhyx = cmsWriteTag(hProfile, 0, (const void *)Data);
    if (ret_cmsWriteTag_yqhyx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsCreateTransform
    const cmsCIExyY qgqoeezc;
    memset(&qgqoeezc, 0, sizeof(qgqoeezc));
    cmsHPROFILE ret_cmsCreateLab2Profile_zqjxa = cmsCreateLab2Profile(&qgqoeezc);

    cmsHTRANSFORM ret_cmsCreateTransform_cgwqk = cmsCreateTransform(ret_cmsCreateLab2Profile_zqjxa, cmsPERCEPTUAL_BLACK_Y, hProfile, cmsPERCEPTUAL_BLACK_X, cmsERROR_FILE, cmsERROR_READ);

    // End mutation: Producer.APPEND_MUTATOR

    cmsMD5computeID(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}