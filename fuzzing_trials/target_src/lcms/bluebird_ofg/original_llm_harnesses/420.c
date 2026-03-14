#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_420(const uint8_t *data, size_t size) {
    // Ensure we have enough data to fill our structures
    if (size < sizeof(cmsCIEXYZ) * 4) {
        return 0;
    }

    // Initialize cmsCIEXYZ structures
    cmsCIEXYZ sourceIlluminant;
    cmsCIEXYZ destIlluminant;
    cmsCIEXYZ sourceWhitePoint;
    cmsCIEXYZ destWhitePoint;

    // Copy data into cmsCIEXYZ structures
    memcpy(&sourceIlluminant, data, sizeof(cmsCIEXYZ));
    memcpy(&destIlluminant, data + sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));
    memcpy(&sourceWhitePoint, data + 2 * sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));
    memcpy(&destWhitePoint, data + 3 * sizeof(cmsCIEXYZ), sizeof(cmsCIEXYZ));

    // Call the function-under-test
    cmsBool result = cmsAdaptToIlluminant(&sourceIlluminant, &destIlluminant, &sourceWhitePoint, &destWhitePoint);

    // Use the result to prevent compiler optimizations
    (void)result;

    return 0;
}