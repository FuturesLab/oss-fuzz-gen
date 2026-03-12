#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters
    cmsContext context = (cmsContext)1; // Example non-NULL context

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsOpenProfileFromMem
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, cmsERROR_FILE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    cmsHPROFILE outputProfile = cmsOpenProfileFromMem(data, size);
    cmsUInt32Number inputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number outputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number intent = INTENT_PERCEPTUAL; // Example intent
    cmsUInt32Number flags = 0; // No flags

    // Ensure that inputProfile and outputProfile are not NULL
    if (inputProfile != NULL && outputProfile != NULL) {
        // Call the function to fuzz
        cmsHTRANSFORM transform = cmsCreateTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);

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


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of cmsGetProfileInfoASCII
    cmsUInt32Number ret_cmsGetProfileInfoASCII_uswxm = cmsGetProfileInfoASCII(outputProfile, 0, uzdstxgy, (const char *)"w", (char *)data, cmsD50Y);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_cmsGetProfileInfoASCII_uswxm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsGetPostScriptCSA
    cmsFloat64Number ret_cmsSetAdaptationState_zafzx = cmsSetAdaptationState(INTENT_PRESERVE_K_PLANE_SATURATION);
    if (ret_cmsSetAdaptationState_zafzx < 0){
    	return 0;
    }
    char nbdqtpnm[1024] = "exvau";

    cmsUInt32Number ret_cmsGetPostScriptCSA_aiyne = cmsGetPostScriptCSA(0, outputProfile, 64, PT_XYZ, nbdqtpnm, (unsigned long )ret_cmsSetAdaptationState_zafzx);
    if (ret_cmsGetPostScriptCSA_aiyne < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        cmsMD5computeID(outputProfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    } return 0;
}