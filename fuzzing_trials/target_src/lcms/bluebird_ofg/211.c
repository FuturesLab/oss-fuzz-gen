#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    cmsFloat64Number temp;
    cmsCIExyY whitePoint;

    // Initialize cmsCIExyY structure with non-NULL values
    whitePoint.x = size > 0 ? ((cmsFloat64Number)data[0] / 255.0) : 0.3127;
    whitePoint.y = size > 1 ? ((cmsFloat64Number)data[1] / 255.0) : 0.3290;
    whitePoint.Y = size > 2 ? ((cmsFloat64Number)data[2] / 255.0) : 1.0;

    // Call the function-under-test
    cmsBool result = cmsTempFromWhitePoint(&temp, &whitePoint);

    // Use the result to avoid compiler optimizations
    if (result) {
        volatile cmsFloat64Number avoid_optimization = temp;
        (void)avoid_optimization;
    }

    return 0;
}