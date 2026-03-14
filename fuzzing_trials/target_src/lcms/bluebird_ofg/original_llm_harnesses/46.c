#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    cmsNAMEDCOLORLIST *originalList = NULL;
    cmsNAMEDCOLORLIST *duplicatedList = NULL;
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Ensure the size is sufficient for creating a named color list
    if (size < 6) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Create a named color list with a single color entry
    originalList = cmsAllocNamedColorList(contextID, 1, 32, "Prefix", "Suffix");
    if (originalList == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Add a color to the named color list
    cmsUInt16Number PCS[3] = { data[2], data[3], 0 };  // Assuming data[2] and data[3] are sufficient
    cmsUInt16Number Colorant[3] = { data[4], data[5], 0 }; // Assuming data[4] and data[5] are sufficient

    // Fix the call to cmsNamedColorInfo by providing correct arguments
    char name[32];
    snprintf(name, sizeof(name), "%c", data[0]); // Use data[0] as a single character name

    cmsNamedColorInfo(originalList, 0, name, "Prefix", "Suffix", PCS, Colorant);

    // Call the function under test
    duplicatedList = cmsDupNamedColorList(originalList);

    // Clean up
    cmsFreeNamedColorList(originalList);
    if (duplicatedList != NULL) {
        cmsFreeNamedColorList(duplicatedList);
    }
    cmsDeleteContext(contextID);

    return 0;
}