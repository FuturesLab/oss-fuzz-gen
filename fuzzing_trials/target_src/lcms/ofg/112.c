#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    cmsNAMEDCOLORLIST *namedColorList;

    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a named color list with some dummy values
    namedColorList = cmsAllocNamedColorList(context, 1, 32, "Prefix", "Suffix");

    // Check if the named color list was created successfully
    if (namedColorList != NULL) {
        // Call the function under test
        cmsFreeNamedColorList(namedColorList);
    }

    // Destroy the memory context
    cmsDeleteContext(context);

    return 0;
}