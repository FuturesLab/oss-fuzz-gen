#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
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
    const char rxmlpbbm[1024] = "gedsm";


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsIT8SetPropertyMulti
    cmsBool ret_cmsIT8SetPropertyMulti_nvgtp = cmsIT8SetPropertyMulti(it8Handle, (const char *)"r", rxmlpbbm, (const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_cmsIT8SetPropertyMulti_nvgtp < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    tableCount = cmsIT8TableCount(it8Handle);

    // Clean up the IT8 handle

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsIT8Free with cmsCIECAM02Done
    cmsCIECAM02Done(it8Handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}