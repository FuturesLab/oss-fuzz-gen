#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"  // Assuming the Little CMS library is used

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Initialize parameters for cmsGDBCheckPoint
    cmsHPROFILE handle = cmsOpenProfileFromMem(data, size);  // Create a handle from the input data
    cmsCIELab cielab;

    // Ensure the handle is not NULL
    if (handle == NULL) {
        return 0;
    }

    // Initialize cmsCIELab with non-NULL values
    cielab.L = 50.0;  // Example value
    cielab.a = 0.0;   // Example value
    cielab.b = 0.0;   // Example value

    // Call the function under test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsSetPCS

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsGetHeaderFlags


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsGetHeaderFlags with cmsGetHeaderModel

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsDetectDestinationBlackPoint
    cmsCIEXYZ erxgjpsk;
    memset(&erxgjpsk, 0, sizeof(erxgjpsk));

    cmsBool ret_cmsDetectDestinationBlackPoint_jcfri = cmsDetectDestinationBlackPoint(&erxgjpsk, handle, 0, PT_MCH11);
    if (ret_cmsDetectDestinationBlackPoint_jcfri < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsUInt32Number ret_cmsGetHeaderFlags_vxdxj = cmsGetHeaderModel(handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_cmsGetHeaderFlags_vxdxj < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of _cmsICCcolorSpace

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetHeaderModel to cmsIT8SetPropertyDbl
    cmsHANDLE ret_cmsIT8Alloc_fygfv = cmsIT8Alloc(0);

    cmsBool ret_cmsIT8SetPropertyDbl_tcpek = cmsIT8SetPropertyDbl(ret_cmsIT8Alloc_fygfv, (const char *)"w", (double )ret_cmsGetHeaderFlags_vxdxj);
    if (ret_cmsIT8SetPropertyDbl_tcpek < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsColorSpaceSignature ret__cmsICCcolorSpace_fwbyg = _cmsICCcolorSpace(cmsSPOT_SQUARE);
    // End mutation: Producer.REPLACE_ARG_MUTATOR




    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsCreateLinearizationDeviceLink

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsSetColorSpace

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsCreateInkLimitingDeviceLinkTHR
    cmsContext ret_cmsGetTransformContextID_sguty = cmsGetTransformContextID(0);

    cmsHPROFILE ret_cmsCreateInkLimitingDeviceLinkTHR_vcukf = cmsCreateInkLimitingDeviceLinkTHR(ret_cmsGetTransformContextID_sguty, ret__cmsICCcolorSpace_fwbyg, PT_HSV);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsCreateInkLimitingDeviceLinkTHR to cmsCreateProofingTransform
    cmsHPROFILE ret_cmsCreateDeviceLinkFromCubeFile_zvlrl = cmsCreateDeviceLinkFromCubeFile((const char *)data);
    cmsHPROFILE ret_cmsCreateNULLProfileTHR_suogo = cmsCreateNULLProfileTHR(0);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsCreateNULLProfileTHR to cmsDetectTAC

    cmsFloat64Number ret_cmsDetectTAC_qykag = cmsDetectTAC(ret_cmsCreateNULLProfileTHR_suogo);
    if (ret_cmsDetectTAC_qykag < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsHTRANSFORM ret_cmsCreateProofingTransform_vitmo = cmsCreateProofingTransform(ret_cmsCreateDeviceLinkFromCubeFile_zvlrl, PT_MCH2, ret_cmsCreateInkLimitingDeviceLinkTHR_vcukf, PT_MCH6, ret_cmsCreateNULLProfileTHR_suogo, PT_MCH14, INTENT_RELATIVE_COLORIMETRIC, cmsSPOT_DIAMOND);

    // End mutation: Producer.APPEND_MUTATOR

    cmsHPROFILE ret_cmsCreate_OkLabProfile_yzdfw = cmsCreate_OkLabProfile(0);

    cmsSetColorSpace(ret_cmsCreate_OkLabProfile_yzdfw, ret__cmsICCcolorSpace_fwbyg);

    // End mutation: Producer.APPEND_MUTATOR

    cmsToneCurve* ret_cmsDupToneCurve_ceffw = cmsDupToneCurve(NULL);
    if (ret_cmsDupToneCurve_ceffw == NULL){
    	return 0;
    }

    cmsHPROFILE ret_cmsCreateLinearizationDeviceLink_stxus = cmsCreateLinearizationDeviceLink(ret__cmsICCcolorSpace_fwbyg, &ret_cmsDupToneCurve_ceffw);

    // End mutation: Producer.APPEND_MUTATOR

    cmsSetPCS(handle, ret__cmsICCcolorSpace_fwbyg);

    // End mutation: Producer.APPEND_MUTATOR

    cmsBool result = cmsGDBCheckPoint(handle, &cielab);

    // Close the profile handle

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
    cmsMD5computeID(handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}