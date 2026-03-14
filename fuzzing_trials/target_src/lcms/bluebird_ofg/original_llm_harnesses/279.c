#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0; // Not enough data to proceed
    }

    // Declare and initialize variables
    cmsContext context = NULL; // Assuming a NULL context for simplicity
    cmsUInt32Number nProfiles = 2; // Number of profiles
    cmsHPROFILE profiles[2] = {cmsCreate_sRGBProfile(), cmsCreate_sRGBProfile()}; // Example profiles
    cmsBool intents[2] = {TRUE, FALSE}; // Example intents
    cmsUInt32Number dwFlags[2] = {0, 0}; // Example flags
    cmsFloat64Number adaptationStates[2] = {1.0, 1.0}; // Example adaptation states
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile(); // Example proofing profile
    cmsUInt32Number intent = INTENT_PERCEPTUAL; // Example rendering intent
    cmsUInt32Number proofingIntent = INTENT_ABSOLUTE_COLORIMETRIC; // Example proofing intent
    cmsUInt32Number dwFlagsTransform = 0; // Example flags for transform
    cmsUInt32Number dwFlagsProofing = 0; // Example flags for proofing

    // Use some of the input data to affect the function call
    intent = *(cmsUInt32Number *)data;
    proofingIntent = *(cmsUInt32Number *)(data + sizeof(cmsUInt32Number));

    // Call the function-under-test
    cmsHTRANSFORM transform = cmsCreateExtendedTransform(
        context,
        nProfiles,
        profiles,
        intents,
        dwFlags,
        adaptationStates,
        proofingProfile,
        intent,
        proofingIntent,
        dwFlagsTransform,
        dwFlagsProofing
    );

    // Clean up
    if (transform != NULL) {
        cmsDeleteTransform(transform);
    }
    for (int i = 0; i < nProfiles; i++) {
        if (profiles[i] != NULL) {
            cmsCloseProfile(profiles[i]);
        }
    }
    if (proofingProfile != NULL) {
        cmsCloseProfile(proofingProfile);
    }

    return 0;
}