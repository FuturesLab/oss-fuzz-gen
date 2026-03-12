#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_421(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsCIEXYZ sourceIlluminant;
    cmsCIEXYZ targetIlluminant;
    cmsCIEXYZ inputColor;
    cmsCIEXYZ adaptedColor;

    // Ensure that the size is enough to extract values for cmsCIEXYZ structures
    if (size < sizeof(cmsCIEXYZ) * 3) {
        return 0;
    }

    // Initialize cmsCIEXYZ structures with data
    sourceIlluminant.X = *((float*)(data));
    sourceIlluminant.Y = *((float*)(data + sizeof(float)));
    sourceIlluminant.Z = *((float*)(data + 2 * sizeof(float)));

    targetIlluminant.X = *((float*)(data + 3 * sizeof(float)));
    targetIlluminant.Y = *((float*)(data + 4 * sizeof(float)));
    targetIlluminant.Z = *((float*)(data + 5 * sizeof(float)));

    inputColor.X = *((float*)(data + 6 * sizeof(float)));
    inputColor.Y = *((float*)(data + 7 * sizeof(float)));
    inputColor.Z = *((float*)(data + 8 * sizeof(float)));

    // Call the function under test
    cmsBool result = cmsAdaptToIlluminant(&adaptedColor, &sourceIlluminant, &targetIlluminant, &inputColor);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}