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

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsMD5computeID with cmsIsMatrixShaper

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromFile to cmsCreateProofingTransform
    const char mrwbegby[1024] = "hyxrl";
    cmsHPROFILE ret_cmsCreateDeviceLinkFromCubeFile_mizsk = cmsCreateDeviceLinkFromCubeFile(mrwbegby);
    cmsHPROFILE ret_cmsCreateNULLProfile_vzvec = cmsCreateNULLProfile();
    cmsFloat64Number ret_cmsDetectTAC_ihdqy = cmsDetectTAC(hProfile);
    if (ret_cmsDetectTAC_ihdqy < 0){
    	return 0;
    }

    cmsHTRANSFORM ret_cmsCreateProofingTransform_hkcqv = cmsCreateProofingTransform(ret_cmsCreateDeviceLinkFromCubeFile_mizsk, cmsReflective, hProfile, PT_MCH15, ret_cmsCreateNULLProfile_vzvec, 0, (unsigned long )ret_cmsDetectTAC_ihdqy, INTENT_ABSOLUTE_COLORIMETRIC);

    // End mutation: Producer.APPEND_MUTATOR

    cmsIsMatrixShaper(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    return 0;
}