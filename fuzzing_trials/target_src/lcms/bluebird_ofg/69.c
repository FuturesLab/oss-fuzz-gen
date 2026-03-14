#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

// Fuzzing harness for cmsGetTransformInputFormat
int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsHPROFILE hProfile;
    cmsUInt32Number inputFormat;
    cmsUInt32Number outputFormat;
    cmsUInt32Number intent;
    cmsUInt32Number flags;

    // Initialize the LCMS library
    cmsSetLogErrorHandler(NULL);

    // Create a dummy profile to use for the transform
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Set up dummy values for transform creation
    inputFormat = TYPE_RGB_8;  // Use a common format
    outputFormat = TYPE_RGB_8; // Use a common format
    intent = INTENT_PERCEPTUAL;
    flags = 0;

    // Create a transform using the dummy profile and formats
    transform = cmsCreateTransform(hProfile, inputFormat, hProfile, outputFormat, intent, flags);
    if (transform == NULL) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number result = cmsGetTransformInputFormat(transform);

    // To maximize fuzzing, use the data input to affect the transform
    if (size >= 3) { // Ensure there's enough data for at least one RGB pixel
        uint8_t input[3];
        input[0] = data[0];
        input[1] = data[1];
        input[2] = data[2];

        // Process the input data with the transform
        uint8_t output[3];
        cmsDoTransform(transform, input, output, 1);
    }

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(hProfile);

    return 0;
}