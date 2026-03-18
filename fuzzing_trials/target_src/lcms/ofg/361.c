#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_361(const uint8_t *data, size_t size) {
    cmsHANDLE handle;

    // Initialize the handle with a valid CIECAM02 context
    cmsViewingConditions conditions;
    conditions.whitePoint.X = 95.047; // D65 standard illuminant
    conditions.whitePoint.Y = 100.0;
    conditions.whitePoint.Z = 108.883;
    conditions.Yb = 20.0;
    conditions.La = 20.0;
    conditions.surround = 1; // Assuming surround is an integer as per the typedef
    conditions.D_value = 64.0;

    handle = cmsCIECAM02Init(NULL, &conditions);

    if (handle != NULL) {
        // Call the function under test
        cmsCIECAM02Done(handle);
    }

    return 0;
}