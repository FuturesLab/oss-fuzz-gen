#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_313(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsCIEXYZ) * 2) {
        return 0;
    }

    // Initialize input and output structures
    cmsCIEXYZ inputXYZ;
    cmsCIEXYZ whitePoint;
    cmsCIELab outputLab;

    // Copy data into input structures
    memcpy(&inputXYZ, data, sizeof(cmsCIEXYZ));
    memcpy(&whitePoint, data + sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));

    // Call the function-under-test
    cmsXYZ2Lab(&whitePoint, &outputLab, &inputXYZ);

    return 0;
}