#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    cmsCIEXYZ inputXYZ;
    cmsCIEXYZ outputXYZ;
    cmsCIELab inputLab;

    // Ensure that the size is sufficient to fill the structures
    if (size < sizeof(cmsCIEXYZ) + sizeof(cmsCIELab)) {
        return 0;
    }

    // Copy data into the input structures
    memcpy(&inputXYZ, data, sizeof(cmsCIEXYZ));
    memcpy(&inputLab, data + sizeof(cmsCIEXYZ), sizeof(cmsCIELab));

    // Call the function under test
    cmsLab2XYZ(&inputXYZ, &outputXYZ, &inputLab);

    return 0;
}