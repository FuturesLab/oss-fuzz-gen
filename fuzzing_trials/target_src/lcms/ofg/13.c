#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform;
    cmsHPROFILE hInProfile, hOutProfile;
    cmsUInt32Number inputFormat, outputFormat;
    cmsUInt32Number result;

    // Initialize LCMS
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Create profiles for input and output
    hInProfile = cmsCreate_sRGBProfile();
    hOutProfile = cmsCreate_sRGBProfile();

    // Set input and output format
    inputFormat = TYPE_RGB_8;
    outputFormat = TYPE_RGB_8;

    // Create a transform with the profiles
    transform = cmsCreateTransform(hInProfile, inputFormat, hOutProfile, outputFormat, INTENT_PERCEPTUAL, 0);

    // Call the function-under-test
    result = cmsGetTransformOutputFormat(transform);

    // Clean up
    cmsDeleteTransform(transform);
    cmsCloseProfile(hInProfile);
    cmsCloseProfile(hOutProfile);
    cmsDeleteContext(contextID);

    return 0;
}