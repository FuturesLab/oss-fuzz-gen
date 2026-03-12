#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"  // Assuming the Little CMS library is used

int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsGetPostScriptCSA
    cmsContext ret_cmsGetTransformContextID_mbpln = cmsGetTransformContextID(0);
    cmsFloat64Number ret_cmsSetAdaptationState_gqykc = cmsSetAdaptationState(FALSE);
    if (ret_cmsSetAdaptationState_gqykc < 0){
    	return 0;
    }
    cmsFloat64Number ret_cmsSetAdaptationState_fvczv = cmsSetAdaptationState(1);
    if (ret_cmsSetAdaptationState_fvczv < 0){
    	return 0;
    }

    cmsUInt32Number ret_cmsGetPostScriptCSA_nfadk = cmsGetPostScriptCSA(ret_cmsGetTransformContextID_mbpln, handle, DIM_SURROUND, (unsigned long )ret_cmsSetAdaptationState_gqykc, (void *)data, (unsigned long )ret_cmsSetAdaptationState_fvczv);
    if (ret_cmsGetPostScriptCSA_nfadk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsUInt32Number ret_cmsGetHeaderFlags_vxdxj = cmsGetHeaderModel(handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_cmsGetHeaderFlags_vxdxj < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsColorSpaceSignature ret__cmsICCcolorSpace_fwbyg = _cmsICCcolorSpace(PT_Lab);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from _cmsICCcolorSpace to cmsCreateLinearizationDeviceLink

    cmsHPROFILE ret_cmsCreateLinearizationDeviceLink_uzdpr = cmsCreateLinearizationDeviceLink(ret__cmsICCcolorSpace_fwbyg, NULL);

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