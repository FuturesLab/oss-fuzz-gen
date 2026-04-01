#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure there's enough data for both cmsCIExyY and cmsCIEXYZ structures
    if (size < sizeof(cmsCIEXYZ)) {
        return 0;
    }

    // Initialize cmsCIExyY and cmsCIEXYZ structures
    cmsCIExyY xyY;
    cmsCIEXYZ XYZ;

    // Copy data into the cmsCIEXYZ structure
    // Ensure that the data size matches the size of cmsCIEXYZ
    memcpy(&XYZ, data, sizeof(cmsCIEXYZ));

    // Call the function-under-test
    cmsXYZ2xyY(&xyY, &XYZ);

    return 0;
}