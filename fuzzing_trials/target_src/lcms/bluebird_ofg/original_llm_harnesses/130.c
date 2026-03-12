#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>
#include <string.h>  // Include string.h for memcpy

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Ensure there's enough data for cmsCIELab structure
    if (size < sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize input and output structures
    cmsCIEXYZ inputXYZ = {0.0, 0.0, 0.0};
    cmsCIEXYZ outputXYZ = {0.0, 0.0, 0.0};
    cmsCIELab inputLab;

    // Copy data to inputLab, ensuring it does not exceed available size
    memcpy(&inputLab, data, sizeof(cmsCIELab));

    // Call the function-under-test
    cmsLab2XYZ(&inputXYZ, &outputXYZ, &inputLab);

    return 0;
}