#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>
#include <string.h>

// Define a function to initialize a cmsNAMEDCOLORLIST with some data
cmsNAMEDCOLORLIST* initializeNamedColorList(const uint8_t *data, size_t size) {
    // Use the input data to define the number of colors and their names
    int numColors = (size > 0) ? data[0] % 10 + 1 : 1; // Limit to a maximum of 10 colors
    cmsNAMEDCOLORLIST* namedColorList = cmsAllocNamedColorList(NULL, numColors, 32, "Prefix", "Suffix");
    if (namedColorList != NULL) {
        for (int i = 0; i < numColors; i++) {
            char colorName[32];
            snprintf(colorName, sizeof(colorName), "ColorName%d", i);
            cmsAppendNamedColor(namedColorList, colorName, NULL, NULL);
        }
    }
    return namedColorList;
}

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize a cmsNAMEDCOLORLIST with some data influenced by the input
    cmsNAMEDCOLORLIST* namedColorList = initializeNamedColorList(data, size);
    if (namedColorList == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Call the function-under-test
    cmsNAMEDCOLORLIST* duplicatedList = cmsDupNamedColorList(namedColorList);

    // Clean up
    if (duplicatedList != NULL) {
        cmsFreeNamedColorList(duplicatedList);
    }
    cmsFreeNamedColorList(namedColorList);

    return 0;
}