#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    // Initialize the cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Initialize cmsViewingConditions with some non-NULL values
    cmsViewingConditions viewingConditions;
    viewingConditions.whitePoint.X = 0.95047; // D65 standard illuminant
    viewingConditions.whitePoint.Y = 1.00000;
    viewingConditions.whitePoint.Z = 1.08883;
    viewingConditions.surround = 0; // Set surround to a valid cmsUInt32Number value
    viewingConditions.Yb = 20.0; // Example value for background luminance
    viewingConditions.La = 318.31; // Example value for adapting luminance
    viewingConditions.D_value = 1.0; // Example value for D_value

    // Call the function under test
    cmsHANDLE handle = cmsCIECAM02Init(context, &viewingConditions);

    // Clean up
    if (handle != NULL) {
        cmsCIECAM02Done(handle);
    }
    cmsDeleteContext(context);

    return 0;
}