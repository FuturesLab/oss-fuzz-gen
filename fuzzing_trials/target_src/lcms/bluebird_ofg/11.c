#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsTagSignature) + sizeof(void*)) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsOpenProfileFromMem
    cmsHPROFILE hProfile = cmsOpenProfileFromMem((const void *)data, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    cmsTagSignature tagSig = *(cmsTagSignature*)data;
    const void *tagData = (const void*)(data + sizeof(cmsTagSignature));

    // Ensure hProfile is valid
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsWriteTag
    char wvrjmxjo[1024] = "yluop";
    cmsBool result = cmsWriteTag(hProfile, tagSig, wvrjmxjo);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Close the profile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsMD5computeID with cmsIsMatrixShaper

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsIsMatrixShaper with cmsMD5computeID

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsMD5computeID with cmsCloseProfile

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsWriteTag to cmsIT8SetTable
    cmsHANDLE ret_cmsIT8Alloc_ibcer = cmsIT8Alloc(0);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsIT8Alloc to cmsCIECAM02Reverse
    const cmsJCh kskpcjoq;
    memset(&kskpcjoq, 0, sizeof(kskpcjoq));
    cmsCIEXYZ tvttlfyy;
    memset(&tvttlfyy, 0, sizeof(tvttlfyy));

    cmsCIECAM02Reverse(ret_cmsIT8Alloc_ibcer, &kskpcjoq, &tvttlfyy);

    // End mutation: Producer.APPEND_MUTATOR

    cmsInt32Number ret_cmsIT8SetTable_ewvqr = cmsIT8SetTable(ret_cmsIT8Alloc_ibcer, (unsigned long )result);
    if (ret_cmsIT8SetTable_ewvqr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsCloseProfile(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}