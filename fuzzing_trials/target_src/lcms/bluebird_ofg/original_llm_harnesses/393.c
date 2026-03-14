#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_393(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for testing
    if (size < 1) {
        return 0;
    }

    // Create a named color list with multiple colors for testing
    cmsNAMEDCOLORLIST *namedColorList = cmsAllocNamedColorList(NULL, 10, 32, "Prefix", "Suffix");
    if (namedColorList == NULL) {
        return 0;
    }

    // Add multiple named colors to the list
    for (int i = 0; i < 10; ++i) {
        char colorName[256];
        snprintf(colorName, sizeof(colorName), "Color%d", i);
        cmsCIEXYZ pcs = {0.0, 0.0, 0.0};
        cmsCIEXYZ deviceColorant = {0.0, 0.0, 0.0};
        cmsAppendNamedColor(namedColorList, colorName, &pcs, &deviceColorant);
    }

    // Use the provided data as a color name, ensuring it is null-terminated
    char fuzzColorName[256];
    size_t copySize = (size < sizeof(fuzzColorName) - 1) ? size : sizeof(fuzzColorName) - 1;
    memcpy(fuzzColorName, data, copySize);
    fuzzColorName[copySize] = '\0';

    // Modify the fuzzColorName to match one of the known names more reliably
    if (size >= 6 && strncmp(fuzzColorName, "Color", 5) == 0 && fuzzColorName[5] >= '0' && fuzzColorName[5] <= '9') {
        // If the fuzz input starts with "Color" and is followed by a digit, ensure it matches one of the added colors
        fuzzColorName[6] = '\0'; // Ensure null-termination
    } else if (size >= 6) {
        // If not matching, force it to match one of the added colors
        snprintf(fuzzColorName, sizeof(fuzzColorName), "Color%d", data[5] % 10);
    }

    // Call the function under test
    cmsInt32Number index = cmsNamedColorIndex(namedColorList, fuzzColorName);

    // Print the index for debugging purposes
    printf("Index of color '%s': %d\n", fuzzColorName, index);

    // Clean up
    cmsFreeNamedColorList(namedColorList);

    return 0;
}