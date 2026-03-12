#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_192(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters
    cmsContext context = (cmsContext)1; // Example non-NULL context
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);
    cmsHPROFILE outputProfile = cmsOpenProfileFromMem(data, size);
    cmsUInt32Number inputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number outputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number intent = INTENT_PERCEPTUAL; // Example intent
    cmsUInt32Number flags = 0; // No flags

    // Ensure that inputProfile and outputProfile are not NULL
    if (inputProfile != NULL && outputProfile != NULL) {
        // Call the function to fuzz

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsCreateTransformTHR

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of cmsCreateTransformTHR
        cmsHTRANSFORM transform = cmsCreateTransformTHR(context, inputProfile, PT_MCH13, outputProfile, cmsERROR_CORRUPTION_DETECTED, intent, flags);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        // End mutation: Producer.REPLACE_ARG_MUTATOR



        // Clean up
        if (transform != NULL) {
            cmsDeleteTransform(transform);
        }
    }

    if (inputProfile != NULL) {
        cmsCloseProfile(inputProfile);
    }
    if (outputProfile != NULL) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsGetProfileInfoASCII
    const char uzdstxgy[1024] = "bxngg";

    cmsUInt32Number ret_cmsGetProfileInfoASCII_uswxm = cmsGetProfileInfoASCII(outputProfile, 0, uzdstxgy, (const char *)"r", (char *)data, cmsD50Y);
    if (ret_cmsGetProfileInfoASCII_uswxm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
        cmsMD5computeID(outputProfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }  return 0;
}