#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_398(const uint8_t *data, size_t size) {
    if (size < 3) {
        // Not enough data to represent a single RGB pixel
        return 0;
    }

    cmsHTRANSFORM transform;
    cmsContext context;

    // Initialize a color transform
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();

    if (inputProfile == NULL || outputProfile == NULL) {
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);

    // Ensure the transform is created successfully
    if (transform != NULL) {
        // Call the function-under-test
        context = cmsGetTransformContextID(transform);

        // Use the transform on the input data
        uint8_t output[3];
        cmsDoTransform(transform, data, output, 1);

        // Cleanup
        cmsDeleteTransform(transform);
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}