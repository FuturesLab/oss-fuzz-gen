#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    if (size < 8) {
        return 0;
    }

    cmsUInt32Number inputFormat = *(cmsUInt32Number*)(data);
    cmsUInt32Number outputFormat = *(cmsUInt32Number*)(data + 4);


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCreate_sRGBProfile with cmsCreateXYZProfile
    cmsHPROFILE hInputProfile = cmsCreateXYZProfile();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCreate_sRGBProfile with cmsCreateNULLProfile
    cmsHPROFILE hOutputProfile = cmsCreateNULLProfile();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    if (hInputProfile == NULL || hOutputProfile == NULL) {
        if (hInputProfile != NULL) {
                cmsCloseProfile(hInputProfile);
        }
        if (hOutputProfile != NULL) {
                cmsCloseProfile(hOutputProfile);
        }
        return 0;
    }

    cmsHTRANSFORM transform = cmsCreateTransform(hInputProfile, inputFormat, hOutputProfile, outputFormat, INTENT_PERCEPTUAL, 0);

    if (transform == NULL) {
        cmsCloseProfile(hInputProfile);
        cmsCloseProfile(hOutputProfile);
        return 0;
    }

    // Create a small buffer to transform
    uint8_t inputBuffer[4] = {0, 0, 0, 0};
    uint8_t outputBuffer[4] = {0};

    // Perform the transformation
    cmsDoTransform(transform, inputBuffer, outputBuffer, 1);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsDoTransform to cmsDoTransformLineStride
    cmsIOHANDLER* ret_cmsGetProfileIOhandler_csoom = cmsGetProfileIOhandler(hOutputProfile);
    if (ret_cmsGetProfileIOhandler_csoom == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetProfileIOhandler to cmsSaveProfileToIOhandler
    cmsHPROFILE ret_cmsCreateNULLProfile_dbfgb = cmsCreateNULLProfile();


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsCreateNULLProfile to cmsDetectRGBProfileGamma

    cmsFloat64Number ret_cmsDetectRGBProfileGamma_rxfks = cmsDetectRGBProfileGamma(hOutputProfile, cmsSPOT_CROSS);
    if (ret_cmsDetectRGBProfileGamma_rxfks < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsUInt32Number ret_cmsSaveProfileToIOhandler_yccff = cmsSaveProfileToIOhandler(ret_cmsCreateNULLProfile_dbfgb, ret_cmsGetProfileIOhandler_csoom);
    if (ret_cmsSaveProfileToIOhandler_yccff < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsDoTransformLineStride(transform, (const void *)ret_cmsGetProfileIOhandler_csoom, outputBuffer, 0, cmsMAX_PATH, PT_MCH12, PT_YCbCr, PT_HLS, PT_MCH12);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsDoTransformLineStride to cmsMLUsetUTF8
    char nwzbhhia[1024] = "jvtjc";

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsDoTransformLineStride to cmsOpenProfileFromFileTHR

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsGetProfileContextID
    cmsContext ret_cmsGetProfileContextID_xoyhe = cmsGetProfileContextID(hOutputProfile);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    cmsBool ret_cmsPlugin_mmuup = cmsPlugin(outputBuffer);
    if (ret_cmsPlugin_mmuup < 0){
    	return 0;
    }

    cmsHPROFILE ret_cmsOpenProfileFromFileTHR_cfxxu = cmsOpenProfileFromFileTHR(ret_cmsGetProfileContextID_xoyhe, (const char *)outputBuffer, (const char *)outputBuffer);

    // End mutation: Producer.APPEND_MUTATOR

    cmsBool ret_cmsPlugin_wilge = cmsPlugin(nwzbhhia);
    if (ret_cmsPlugin_wilge < 0){
    	return 0;
    }

    cmsBool ret_cmsMLUsetUTF8_dejuh = cmsMLUsetUTF8(NULL, (const char *)"w", (const char *)outputBuffer, (const char *)nwzbhhia);
    if (ret_cmsMLUsetUTF8_dejuh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsDeleteTransform(transform);
    cmsCloseProfile(hInputProfile);
    cmsCloseProfile(hOutputProfile);

    return 0;
}