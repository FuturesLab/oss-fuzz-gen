#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsCreateNULLProfile to cmsSetHeaderManufacturer

    cmsSetHeaderManufacturer(ret_cmsCreateNULLProfile_dbfgb, INTENT_PERCEPTUAL);

    // End mutation: Producer.APPEND_MUTATOR

    cmsUInt32Number ret_cmsSaveProfileToIOhandler_yccff = cmsSaveProfileToIOhandler(ret_cmsCreateNULLProfile_dbfgb, ret_cmsGetProfileIOhandler_csoom);
    if (ret_cmsSaveProfileToIOhandler_yccff < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsDoTransformLineStride(transform, (const void *)ret_cmsGetProfileIOhandler_csoom, outputBuffer, 0, cmsMAX_PATH, PT_MCH12, PT_YCbCr, PT_HLS, PT_MCH12);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsDoTransformLineStride to cmsMLUsetUTF8
    cmsMLU* ret_cmsMLUdup_kcpcx = cmsMLUdup(NULL);
    if (ret_cmsMLUdup_kcpcx == NULL){
    	return 0;
    }
    void* ret_cmsStageData_bkvni = cmsStageData(NULL);
    if (ret_cmsStageData_bkvni == NULL){
    	return 0;
    }
    cmsBool ret_cmsPlugin_txdyv = cmsPlugin(outputBuffer);
    if (ret_cmsPlugin_txdyv < 0){
    	return 0;
    }

    cmsBool ret_cmsMLUsetUTF8_kdyej = cmsMLUsetUTF8(ret_cmsMLUdup_kcpcx, (const char *)outputBuffer, (const char *)ret_cmsStageData_bkvni, (const char *)outputBuffer);
    if (ret_cmsMLUsetUTF8_kdyej < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsDeleteTransform(transform);
    cmsCloseProfile(hInputProfile);
    cmsCloseProfile(hOutputProfile);

    return 0;
}