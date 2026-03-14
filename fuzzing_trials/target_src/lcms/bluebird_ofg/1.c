#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsFloat64Number version;
    cmsUInt32Number flags;
    cmsHPROFILE profile;

    // Initialize the parameters with non-NULL values
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsGetPostScriptColorResource
    cmsContext ret_cmsGetProfileContextID_swxqr = cmsGetProfileContextID(0);
    cmsIOHANDLER* ret_cmsGetProfileIOhandler_ekvjv = cmsGetProfileIOhandler(inputProfile);
    if (ret_cmsGetProfileIOhandler_ekvjv == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of cmsGetPostScriptColorResource
    cmsUInt32Number ret_cmsGetPostScriptColorResource_lavuc = cmsGetPostScriptColorResource(ret_cmsGetProfileContextID_swxqr, 0, inputProfile, cmsERROR_INTERNAL, PT_RGB, ret_cmsGetProfileIOhandler_ekvjv);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_cmsGetPostScriptColorResource_lavuc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    if (inputProfile == NULL || outputProfile == NULL) {
        if (inputProfile != NULL) {
                cmsCloseProfile(inputProfile);
        }
        if (outputProfile != NULL) {
                cmsCloseProfile(outputProfile);
        }
        return 0;
    }

    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    version = 4.3; // Example version number
    flags = 0; // Example flags, can be varied

    // Ensure transform is valid before proceeding
    if (transform == NULL) {
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of cmsTransform2DeviceLink

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsCreateTransform to cmsDoTransformStride
    cmsIOHANDLER* ret_cmsOpenIOhandlerFromNULL_cveoo = cmsOpenIOhandlerFromNULL(0);
    if (ret_cmsOpenIOhandlerFromNULL_cveoo == NULL){
    	return 0;
    }
    char waznzlmb[1024] = "wnqup";

    cmsDoTransformStride(transform, (const void *)ret_cmsOpenIOhandlerFromNULL_cveoo, waznzlmb, cmsSPOT_CROSS, PT_MCH13);

    // End mutation: Producer.APPEND_MUTATOR

    profile = cmsTransform2DeviceLink(transform, version, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (profile != NULL) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
        cmsMD5computeID(profile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}