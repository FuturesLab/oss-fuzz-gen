#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsContext context = (cmsContext)data; // Cast data to cmsContext
    cmsCIExyY whitePoint;

    // Ensure the size is sufficient for cmsCIExyY structure
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Copy data into the whitePoint structure
    whitePoint.x = *((double*)data);
    whitePoint.y = *((double*)(data + sizeof(double)));
    whitePoint.Y = *((double*)(data + 2 * sizeof(double)));

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateLab4ProfileTHR(context, &whitePoint);

    // Clean up if necessary
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}