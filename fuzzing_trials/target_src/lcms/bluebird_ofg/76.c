#include <stdint.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number dwFlags;
    cmsBool bInput;

    // Initialize variables with non-null values
    hProfile = cmsOpenProfileFromMem(data, size);
    dwFlags = size > 0 ? data[0] : 0;  // Use first byte of data as flags if available
    bInput = (size > 1) ? (data[1] % 2 == 0) : 1;  // Use second byte of data to determine boolean value

    if (hProfile != NULL) {
        // Call the function-under-test
        cmsUInt32Number result = cmsFormatterForPCSOfProfile(hProfile, dwFlags, bInput);

        // Close the profile to avoid memory leaks

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsFormatterForPCSOfProfile to cmsGetPostScriptCRD
        cmsContext ret_cmsGetProfileContextID_bbcda = cmsGetProfileContextID(0);

        cmsUInt32Number ret_cmsGetPostScriptCRD_yswek = cmsGetPostScriptCRD(ret_cmsGetProfileContextID_bbcda, hProfile, cmsPERCEPTUAL_BLACK_Y, result, NULL, INTENT_PRESERVE_K_ONLY_SATURATION);
        if (ret_cmsGetPostScriptCRD_yswek < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cmsCloseProfile(hProfile);
    }
    return 0;
}