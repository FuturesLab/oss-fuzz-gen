#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsCIExyY)) {
        return 0; // Not enough data to fill cmsCIExyY structure
    }

    cmsCIExyY whitePoint;
    // Copy data into the cmsCIExyY structure
    memcpy(&whitePoint, data, sizeof(cmsCIExyY));

    // Ensure the values are within a reasonable range for color coordinates
    if (whitePoint.x < 0.0 || whitePoint.x > 1.0 ||
        whitePoint.y < 0.0 || whitePoint.y > 1.0 ||
        whitePoint.Y < 0.0 || whitePoint.Y > 1.0) {
        return 0;
    }

    // Call the function under test
    cmsHPROFILE profile = cmsCreateLab2Profile(&whitePoint);

    // If a profile was created, free it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}