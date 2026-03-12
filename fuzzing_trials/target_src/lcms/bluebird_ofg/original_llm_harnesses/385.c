#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_385(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for cmsxyY2XYZ
    cmsCIEXYZ xyz;
    cmsCIExyY xyY;

    // Ensure the data is large enough to populate cmsCIExyY
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Copy data into cmsCIExyY structure
    const cmsCIExyY *input_xyY = (const cmsCIExyY *)data;

    // Call the function-under-test
    cmsxyY2XYZ(&xyz, input_xyY);

    return 0;
}