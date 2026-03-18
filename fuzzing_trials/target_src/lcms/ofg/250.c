#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsCIExyY whitePoint;

    // Ensure the input size is sufficient for cmsCIExyY structure
    if (size < sizeof(cmsCIExyY)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Populate the cmsCIExyY structure with data
    whitePoint.x = ((const float*)data)[0];
    whitePoint.y = ((const float*)data)[1];
    whitePoint.Y = ((const float*)data)[2];

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateLab2ProfileTHR(context, &whitePoint);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}