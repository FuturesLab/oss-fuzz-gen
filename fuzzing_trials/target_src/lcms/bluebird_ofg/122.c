#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters
    cmsContext context = (cmsContext)1; // Example non-NULL context

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsOpenProfileFromMem
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem((const void *)data, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsCreateMultiprofileTransform


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of cmsCreateMultiprofileTransform
    cmsHTRANSFORM ret_cmsCreateMultiprofileTransform_qzakn = cmsCreateMultiprofileTransform(&inputProfile, cmsERROR_UNDEFINED, cmsERROR_WRITE, PT_YCbCr, cmsMAX_PATH, PT_GRAY);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
        cmsMD5computeID(inputProfile);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }
    if (outputProfile != NULL) {
        cmsCloseProfile(outputProfile);
    }  return 0;
}