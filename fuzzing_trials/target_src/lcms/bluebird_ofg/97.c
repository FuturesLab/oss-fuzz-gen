#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    cmsHANDLE it8Handle = NULL;
    cmsUInt32Number tableCount;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize the IT8 handle with the data
    it8Handle = cmsIT8LoadFromMem(NULL, data, size);  // Pass NULL for the cmsContext
    if (it8Handle == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsIT8LoadFromMem to cmsIT8SetPropertyMulti
    char ulqbooyg[1024] = "snykl";

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsIT8LoadFromMem to cmsIT8SetPropertyUncooked
    const char gklnxqti[1024] = "ncami";


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsIT8SetPropertyUncooked with cmsIT8SetPropertyStr
    cmsBool ret_cmsIT8SetPropertyUncooked_bdbrz = cmsIT8SetPropertyStr(it8Handle, (const char *)"r", gklnxqti);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_cmsIT8SetPropertyUncooked_bdbrz < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsBool ret_cmsPlugin_dcshk = cmsPlugin(ulqbooyg);
    if (ret_cmsPlugin_dcshk < 0){
    	return 0;
    }
    void* ret_cmsGetContextUserData_wohrb = cmsGetContextUserData(0);
    if (ret_cmsGetContextUserData_wohrb == NULL){
    	return 0;
    }
    void* ret_cmsStageData_duupq = cmsStageData(NULL);
    if (ret_cmsStageData_duupq == NULL){
    	return 0;
    }

    cmsBool ret_cmsIT8SetPropertyMulti_kozzd = cmsIT8SetPropertyMulti(it8Handle, (const char *)ulqbooyg, (const char *)ret_cmsGetContextUserData_wohrb, (const char *)ret_cmsStageData_duupq);
    if (ret_cmsIT8SetPropertyMulti_kozzd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tableCount = cmsIT8TableCount(it8Handle);

    // Clean up the IT8 handle
    cmsIT8Free(it8Handle);

    return 0;
}