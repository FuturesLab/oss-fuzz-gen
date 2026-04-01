#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    cmsHTRANSFORM transform = NULL;
    cmsUInt32Number inputFormat;

    // Check if the data size is sufficient to create a transform
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Create a dummy color profile for the source and destination
    cmsHPROFILE srcProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE dstProfile = cmsCreate_sRGBProfile();

    if (srcProfile == NULL || dstProfile == NULL) {
        if (srcProfile != NULL) cmsCloseProfile(srcProfile);
        if (dstProfile != NULL) cmsCloseProfile(dstProfile);
        return 0;
    }

    // Create a transform using the data as input for the format
    cmsUInt32Number inputFormatData = *(cmsUInt32Number*)data;
    cmsUInt32Number outputFormatData = *(cmsUInt32Number*)(data + sizeof(cmsUInt32Number));

    transform = cmsCreateTransform(srcProfile, inputFormatData, dstProfile, outputFormatData, INTENT_PERCEPTUAL, 0);

    // Clean up profiles
    cmsCloseProfile(srcProfile);
    cmsCloseProfile(dstProfile);

    if (transform == NULL) {
        return 0;
    }

    // Call the function under test
    inputFormat = cmsGetTransformInputFormat(transform);

    // Clean up transform
    cmsDeleteTransform(transform);

    return 0;
}