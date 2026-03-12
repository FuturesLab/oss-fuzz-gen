#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsTagSignature) + sizeof(void*)) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cmsOpenProfileFromMem
    cmsHPROFILE hProfile = cmsOpenProfileFromMem((const void *)data, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    cmsTagSignature tagSig = *(cmsTagSignature*)data;
    const void *tagData = (const void*)(data + sizeof(cmsTagSignature));

    // Ensure hProfile is valid
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cmsOpenProfileFromMem to cmsSetHeaderFlags


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cmsSetHeaderFlags
    cmsSetHeaderFlags(hProfile, PT_MCH10);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    cmsBool result = cmsWriteTag(hProfile, tagSig, tagData);

    // Close the profile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsMD5computeID with cmsIsMatrixShaper

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsIsMatrixShaper with cmsMD5computeID

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsMD5computeID with cmsCloseProfile

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsCloseProfile with cmsMD5computeID
    cmsMD5computeID(hProfile);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}