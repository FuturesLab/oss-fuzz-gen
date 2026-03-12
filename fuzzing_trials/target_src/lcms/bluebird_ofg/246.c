#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters
    cmsContext context = (cmsContext)1; // Example non-NULL context

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsOpenProfileFromMem
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, cmsTransparency);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsCreateExtendedTransform
    cmsContext ret_cmsGetTransformContextID_nvrxt = cmsGetTransformContextID(0);
    cmsBool ret_cmsCloseProfile_nhdqo = cmsCloseProfile(inputProfile);
    if (ret_cmsCloseProfile_nhdqo < 0){
    	return 0;
    }
    cmsHPROFILE wryrekvl;
    memset(&wryrekvl, 0, sizeof(wryrekvl));
    cmsUInt32Number rvzzpvdx = 0;
    cmsFloat64Number dpsbhkwc = 1;

    cmsHTRANSFORM ret_cmsCreateExtendedTransform_qkdoc = cmsCreateExtendedTransform(ret_cmsGetTransformContextID_nvrxt, 0, &wryrekvl, &ret_cmsCloseProfile_nhdqo, &rvzzpvdx, &dpsbhkwc, inputProfile, cmsERROR_FILE, cmsNoLanguage, 1, PT_YCbCr);

    // End mutation: Producer.APPEND_MUTATOR

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

    cmsUInt32Number ret_cmsGetProfileInfoASCII_uswxm = cmsGetProfileInfoASCII(outputProfile, 0, uzdstxgy, (const char *)"r", (char *)data, cmsD50Y);
    if (ret_cmsGetProfileInfoASCII_uswxm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsIsMatrixShaper
        cmsIsMatrixShaper(outputProfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }  return 0;
}