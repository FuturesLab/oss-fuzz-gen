#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to initialize cmsCIEXYZ
    if (size < sizeof(cmsCIEXYZ)) {
        return 0;
    }

    // Initialize cmsCIEXYZ structure from input data
    cmsCIEXYZ xyz;
    xyz.X = *(const float *)(data);
    xyz.Y = *(const float *)(data + sizeof(float));
    xyz.Z = *(const float *)(data + 2 * sizeof(float));

    // Declare and initialize cmsUInt16Number array
    cmsUInt16Number encodedXYZ[3] = {0, 0, 0};

    // Call the function-under-test
    cmsFloat2XYZEncoded(encodedXYZ, &xyz);

    return 0;
}