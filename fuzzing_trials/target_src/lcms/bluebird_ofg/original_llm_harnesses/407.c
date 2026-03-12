#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_407(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    cmsContext context;
    cmsHPROFILE inputProfile;
    cmsHPROFILE outputProfile;
    cmsHPROFILE proofingProfile;
    cmsUInt32Number inputFormat;
    cmsUInt32Number outputFormat;
    cmsUInt32Number proofingIntent;
    cmsUInt32Number transformIntent;
    cmsUInt32Number flags;

    // Initialize the context
    context = cmsCreateContext(NULL, NULL);

    // Create dummy profiles for input, output, and proofing
    inputProfile = cmsCreate_sRGBProfile();
    outputProfile = cmsCreate_sRGBProfile();
    proofingProfile = cmsCreate_sRGBProfile();

    // Set some non-zero values for formats and intents
    inputFormat = TYPE_RGB_8;
    outputFormat = TYPE_RGB_8;
    proofingIntent = INTENT_RELATIVE_COLORIMETRIC;
    transformIntent = INTENT_PERCEPTUAL;
    flags = cmsFLAGS_SOFTPROOFING;

    // Call the function-under-test
    cmsHTRANSFORM transform = cmsCreateProofingTransformTHR(
        context,
        inputProfile,
        inputFormat,
        outputProfile,
        outputFormat,
        proofingProfile,
        proofingIntent,
        transformIntent,
        flags
    );

    // Clean up
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);
    cmsDeleteContext(context);

    return 0;
}