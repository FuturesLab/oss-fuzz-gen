#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsContext context = (cmsContext)1; // Dummy non-NULL context
    cmsCIExyY whitePoint;

    // Ensure data is large enough to populate cmsCIExyY structure
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Populate the cmsCIExyY structure from the input data
    const double *doubleData = (const double *)data;
    whitePoint.x = doubleData[0];
    whitePoint.y = doubleData[1];
    whitePoint.Y = doubleData[2];

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateLab4ProfileTHR(context, &whitePoint);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}