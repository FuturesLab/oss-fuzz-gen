#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    cmsNAMEDCOLORLIST *namedColorList = NULL;
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a named color list with a small number of colors for testing
    namedColorList = cmsAllocNamedColorList(context, 2, 32, "Prefix", "Suffix");
    if (namedColorList != NULL) {
        // Add some dummy named colors to the list
        if (size >= 2 * sizeof(cmsUInt16Number)) {
            cmsAppendNamedColor(namedColorList, "Color1", (const cmsUInt16Number *)data, (const cmsUInt16Number *)data);
            cmsAppendNamedColor(namedColorList, "Color2", (const cmsUInt16Number *)(data + 1), (const cmsUInt16Number *)(data + 1));
        }

        // Call the function-under-test
        cmsFreeNamedColorList(namedColorList);
    }

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}