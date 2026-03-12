#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_486(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE inputProfile = NULL;
    cmsHPROFILE outputProfile = NULL;
    cmsUInt32Number inputFormat = TYPE_RGB_8; // Example format, can vary
    cmsUInt32Number outputFormat = TYPE_RGB_8; // Example format, can vary
    cmsUInt32Number intent = INTENT_PERCEPTUAL; // Example intent, can vary
    cmsUInt32Number flags = 0; // Example flags, can vary

    // Create profiles from the data if size is sufficient
    if (size > 128) { // Ensure enough data for profile creation
        inputProfile = cmsOpenProfileFromMem(data, size / 2);
        outputProfile = cmsOpenProfileFromMem(data + size / 2, size / 2);
    }

    // Ensure profiles are not NULL
    if (inputProfile != NULL && outputProfile != NULL) {
        // Call the function-under-test
        cmsHTRANSFORM transform = cmsCreateTransform(
            inputProfile, inputFormat, outputProfile, outputFormat, intent, flags
        );

        // Clean up
        cmsDeleteTransform(transform);
    }

    // Close profiles if they were opened
    if (inputProfile != NULL) {
        cmsCloseProfile(inputProfile);
    }
    if (outputProfile != NULL) {
        cmsCloseProfile(outputProfile);
    }

    return 0;
}