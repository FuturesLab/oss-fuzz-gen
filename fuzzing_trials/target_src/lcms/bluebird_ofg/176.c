#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsFloat64Number version;
    cmsUInt32Number flags;
    cmsHPROFILE profile;

    // Initialize the parameters with non-NULL values
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsGetPostScriptColorResource
    cmsContext ret_cmsGetTransformContextID_cpuvm = cmsGetTransformContextID(0);
    cmsIOHANDLER* ret_cmsGetProfileIOhandler_ekvjv = cmsGetProfileIOhandler(inputProfile);
    if (ret_cmsGetProfileIOhandler_ekvjv == NULL){
    	return 0;
    }

    cmsUInt32Number ret_cmsGetPostScriptColorResource_zfgve = cmsGetPostScriptColorResource(ret_cmsGetTransformContextID_cpuvm, 0, inputProfile, cmsSPOT_PRINTER_DEFAULT, PT_MCH7, ret_cmsGetProfileIOhandler_ekvjv);
    if (ret_cmsGetPostScriptColorResource_zfgve < 0){
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
    profile = cmsTransform2DeviceLink(transform, version, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}