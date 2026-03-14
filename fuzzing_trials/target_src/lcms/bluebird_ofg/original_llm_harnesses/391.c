#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_391(const uint8_t *data, size_t size) {
    if (size < 3 * sizeof(double)) {
        return 0; // Not enough data
    }

    // Construct a cmsCIEXYZ structure from the input data
    cmsCIEXYZ inputXYZ;
    inputXYZ.X = ((double *)data)[0];
    inputXYZ.Y = ((double *)data)[1];
    inputXYZ.Z = ((double *)data)[2];

    cmsCIExyY outputxyY;

    // Use the function under test
    cmsXYZ2xyY(&outputxyY, &inputXYZ);

    // Access the fields of the cmsCIExyY structure to ensure they are valid.
    volatile double x = outputxyY.x;
    volatile double y = outputxyY.y;
    volatile double Y = outputxyY.Y;

    return 0;
}