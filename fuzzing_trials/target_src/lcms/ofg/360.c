#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_360(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsViewingConditions)) {
        return 0; // Not enough data to fill cmsViewingConditions
    }

    cmsHANDLE handle = NULL;

    // Initialize the handle with a default non-NULL value
    cmsCIEXYZ whitePoint = {0.95047, 1.00000, 1.08883}; // D65 standard illuminant

    // Create a cmsViewingConditions structure from the input data
    cmsViewingConditions vc;
    memcpy(&vc, data, sizeof(cmsViewingConditions));

    // Ensure the white point values are valid
    vc.whitePoint.X = whitePoint.X;
    vc.whitePoint.Y = whitePoint.Y;
    vc.whitePoint.Z = whitePoint.Z;

    handle = cmsCIECAM02Init(NULL, &vc);
    if (handle != NULL) {
        // Perform some operations with the handle to increase code coverage
        cmsCIECAM02Done(handle);
    }

    return 0;
}