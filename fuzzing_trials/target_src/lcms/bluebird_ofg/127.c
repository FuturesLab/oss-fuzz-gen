#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters
    cmsContext context = (cmsContext)1; // Example non-NULL context
    cmsHPROFILE inputProfile = cmsOpenProfileFromMem(data, size);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsOpenProfileFromMem
    cmsHPROFILE outputProfile = cmsOpenProfileFromMem(NULL, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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
        cmsCloseProfile(inputProfile);
    }
    if (outputProfile != NULL) {
        cmsCloseProfile(outputProfile);
    }
    return 0;
}