#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHTRANSFORM transform;
    cmsHPROFILE inputProfile, outputProfile;
    cmsUInt32Number inputFormat, outputFormat;
    cmsUInt32Number sizeOfTransform = 1; // Set to a non-zero value

    // Check if the input size is sufficient
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Create input and output profiles
    inputProfile = cmsCreate_sRGBProfile();
    outputProfile = cmsCreate_sRGBProfile();

    // Define input and output formats
    inputFormat = TYPE_RGB_8;
    outputFormat = TYPE_RGB_8;

    // Create a transform
    transform = cmsCreateTransform(inputProfile, inputFormat, 
                                   outputProfile, outputFormat, 
                                   INTENT_PERCEPTUAL, 0);

    // Allocate memory for input and output buffers
    const void *inputBuffer = (const void *)data;
    void *outputBuffer = malloc(size);
    if (outputBuffer == NULL) {
        cmsDeleteTransform(transform);
        cmsCloseProfile(inputProfile);
        cmsCloseProfile(outputProfile);
        return 0;
    }

    // Call the function-under-test
    cmsDoTransform(transform, inputBuffer, outputBuffer, sizeOfTransform);

    // Clean up
    free(outputBuffer);
    cmsDeleteTransform(transform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);

    return 0;
}