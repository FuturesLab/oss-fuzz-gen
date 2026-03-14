#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_386(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract values for cmsCIExyY
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Initialize cmsCIExyY with data
    cmsCIExyY input_xyY;
    input_xyY.x = *(double *)(data);
    input_xyY.y = *(double *)(data + sizeof(double));
    input_xyY.Y = *(double *)(data + 2 * sizeof(double));

    // Initialize cmsCIEXYZ structure
    cmsCIEXYZ output_XYZ;
    output_XYZ.X = 0.0;
    output_XYZ.Y = 0.0;
    output_XYZ.Z = 0.0;

    // Call the function-under-test
    cmsxyY2XYZ(&output_XYZ, &input_xyY);

    return 0;
}