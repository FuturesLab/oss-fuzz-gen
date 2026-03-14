#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"  // Assuming the Little CMS library is used

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
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
    cmsUInt32Number ret_cmsGetHeaderFlags_vxdxj = cmsGetHeaderModel(handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_cmsGetHeaderFlags_vxdxj < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of _cmsICCcolorSpace

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of _cmsICCcolorSpace
    cmsColorSpaceSignature ret__cmsICCcolorSpace_fwbyg = _cmsICCcolorSpace(PT_MCH8);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR




    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsCreateLinearizationDeviceLink

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsSetColorSpace

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsCreateInkLimitingDeviceLinkTHR
    cmsContext ret_cmsGetTransformContextID_sguty = cmsGetTransformContextID(0);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetTransformContextID to cmsCreateBCHSWabstractProfileTHR

    cmsHPROFILE ret_cmsCreateBCHSWabstractProfileTHR_trpqa = cmsCreateBCHSWabstractProfileTHR(ret_cmsGetTransformContextID_sguty, cmsERROR_UNKNOWN_EXTENSION, PT_MCH10, cmsERROR_READ, PT_YCbCr, INTENT_ABSOLUTE_COLORIMETRIC, INTENT_SATURATION, TRUE);

    // End mutation: Producer.APPEND_MUTATOR

    cmsHPROFILE ret_cmsCreateInkLimitingDeviceLinkTHR_vcukf = cmsCreateInkLimitingDeviceLinkTHR(ret_cmsGetTransformContextID_sguty, ret__cmsICCcolorSpace_fwbyg, PT_HSV);

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