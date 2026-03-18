#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_404(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to handle the transform
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Initialize variables
    cmsHTRANSFORM transform;
    const void *inputBuffer = (const void *)data;
    void *outputBuffer = malloc(size); // Allocate memory for the output buffer
    cmsUInt32Number sizeOfElement = sizeof(cmsUInt32Number);
    cmsUInt32Number stride = sizeOfElement;

    // Create a simple transform for testing purposes
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    transform = cmsCreateTransform(inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);

    // Call the function-under-test
    cmsDoTransformStride(transform, inputBuffer, outputBuffer, size / sizeOfElement, stride);

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    free(outputBuffer);

    return 0;
}