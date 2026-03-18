#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_392(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a cmsNAMEDCOLORLIST object
    cmsNAMEDCOLORLIST *namedColorList = cmsAllocNamedColorList(NULL, 1, 32, "Prefix", "Suffix");
    if (namedColorList == NULL) {
        return 0;
    }

    // Add a named color to the list
    char sampleColorName[32];
    strncpy(sampleColorName, "SampleColor", sizeof(sampleColorName) - 1);
    sampleColorName[sizeof(sampleColorName) - 1] = '\0'; // Ensure null-termination
    cmsAppendNamedColor(namedColorList, sampleColorName, NULL, NULL);

    // Copy the input data into a null-terminated string
    char *colorName = (char *)malloc(size + 1);
    if (colorName == NULL) {
        cmsFreeNamedColorList(namedColorList);
        return 0;
    }
    memcpy(colorName, data, size);
    colorName[size] = '\0'; // Null-terminate the string

    // Call the function under test
    cmsInt32Number index = cmsNamedColorIndex(namedColorList, colorName);

    // Check if the index is valid to increase code coverage
    if (index >= 0) {
        // Do something with the valid index if needed
        // For example, retrieve the color using the valid index
        char retrievedColorName[32];
        char retrievedPrefix[32];
        char retrievedSuffix[32];
        cmsUInt16Number pcs[3];
        cmsUInt16Number colorant[3];
        cmsNamedColorInfo(namedColorList, index, retrievedColorName, retrievedPrefix, retrievedSuffix, pcs, colorant);
    }

    // Clean up
    free(colorName);
    cmsFreeNamedColorList(namedColorList);

    return 0;
}