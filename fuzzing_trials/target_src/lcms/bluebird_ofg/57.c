#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    if (size < 4) {
        // Not enough data to create a valid profile
        return 0;
    }

    // Create a memory-based input profile from the data
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);
    if (inputProfile == NULL) {
        return 0;
    }

    // Create a sRGB output profile
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    if (outputProfile == NULL) {
        cmsCloseProfile(inputProfile);
        return 0;
    }

    // Create a transform from the input profile to the sRGB profile
    cmsHTRANSFORM transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (transform == NULL) {
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    // Call the function-under-test
    cmsNAMEDCOLORLIST *namedColorList = cmsGetNamedColorList(transform);

    // Check the result (optional, depending on what you want to do with it)
    if (namedColorList != NULL) {
        // Process namedColorList if needed
    }

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsGetNamedColorList to cmsIT8SaveToMem
    cmsHANDLE ret_cmsDictAlloc_bcogs = cmsDictAlloc(0);
    cmsUInt32Number ret_cmsGetHeaderFlags_lokkj = cmsGetHeaderFlags(outputProfile);
    if (ret_cmsGetHeaderFlags_lokkj < 0){
    	return 0;
    }

    cmsBool ret_cmsIT8SaveToMem_ysijh = cmsIT8SaveToMem(ret_cmsDictAlloc_bcogs, (void *)namedColorList, &ret_cmsGetHeaderFlags_lokkj);
    if (ret_cmsIT8SaveToMem_ysijh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}