#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE inputProfile = NULL;
    cmsHPROFILE outputProfile = NULL;
    cmsHPROFILE proofingProfile = NULL;
    cmsUInt32Number inputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number outputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number proofingIntent = INTENT_RELATIVE_COLORIMETRIC;
    cmsUInt32Number flags = cmsFLAGS_SOFTPROOFING;
    cmsUInt32Number proofingFlags = cmsFLAGS_SOFTPROOFING;

    // Initialize the profiles
    inputProfile = cmsOpenProfileFromMem(data, size);
    if (inputProfile == NULL) return 0;

    outputProfile = cmsOpenProfileFromMem(data, size);
    if (outputProfile == NULL) {
        cmsCloseProfile(inputProfile);
        return 0;
    }

    proofingProfile = cmsOpenProfileFromMem(data, size);
    if (proofingProfile == NULL) {
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    // Call the function-under-test
    cmsHTRANSFORM transform = cmsCreateProofingTransform(
        inputProfile, inputFormat,
        outputProfile, outputFormat,
        proofingProfile, proofingIntent,
        flags, proofingFlags
    );

    // Cleanup
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);

    return 0;
}