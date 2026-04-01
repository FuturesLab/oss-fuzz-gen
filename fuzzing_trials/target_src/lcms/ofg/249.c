#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    cmsContext context;
    cmsCIExyY whitePoint;
    cmsHPROFILE profile;

    // Initialize context with non-NULL value
    context = cmsCreateContext(NULL, NULL);

    // Ensure size is sufficient to extract cmsCIExyY values
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Initialize whitePoint with data
    whitePoint.x = *(const double *)data;
    whitePoint.y = *(const double *)(data + sizeof(double));
    whitePoint.Y = *(const double *)(data + 2 * sizeof(double));

    // Call the function-under-test
    profile = cmsCreateLab2ProfileTHR(context, &whitePoint);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}