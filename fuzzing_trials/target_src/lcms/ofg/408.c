#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_408(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = (cmsContext)1; // Using a non-NULL dummy context
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile(); // Create a simple sRGB profile
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile(); // Create another sRGB profile for output
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile(); // Create a proofing profile
    cmsUInt32Number inputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number outputFormat = TYPE_RGB_8; // Example format
    cmsUInt32Number proofingIntent = INTENT_ABSOLUTE_COLORIMETRIC; // Example intent
    cmsUInt32Number flags = 0; // No special flags
    cmsUInt32Number proofingFlags = cmsFLAGS_SOFTPROOFING; // Example proofing flag

    // Call the function under test
    cmsHTRANSFORM transform = cmsCreateProofingTransformTHR(
        context,
        inputProfile,
        inputFormat,
        outputProfile,
        outputFormat,
        proofingProfile,
        proofingIntent,
        flags,
        proofingFlags
    );

    // Clean up
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);

    return 0;
}