#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <lcms2.h>

extern int LLVMFuzzerTestOneInput_286(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0;  // Not enough data to proceed
    }

    cmsNAMEDCOLORLIST *namedColorList = NULL;
    cmsContext contextID = cmsCreateContext(NULL, NULL);

    // Use the first byte of data to determine the number of colors (limit to 10 for safety)
    int numColors = data[0] % 10 + 1;

    // Create a named color list with the determined number of colors
    namedColorList = cmsAllocNamedColorList(contextID, numColors, 32, "Prefix", "Suffix");
    if (namedColorList == NULL) {
        cmsDeleteContext(contextID);
        return 0;
    }

    // Add colors to the named color list using input data
    for (int i = 0; i < numColors; i++) {
        char name[32];
        snprintf(name, sizeof(name), "Color%d", i);

        // Use subsequent bytes of data to determine PCS and colorant values
        cmsUInt16Number PCS[3] = { (cmsUInt16Number)(data[(i * 3 + 1) % size] * 256), 
                                   (cmsUInt16Number)(data[(i * 3 + 2) % size] * 256), 
                                   (cmsUInt16Number)(data[(i * 3 + 3) % size] * 256) };
        cmsUInt16Number colorant[3] = { (cmsUInt16Number)(data[(i * 3 + 1) % size] * 256), 
                                        (cmsUInt16Number)(data[(i * 3 + 2) % size] * 256), 
                                        (cmsUInt16Number)(data[(i * 3 + 3) % size] * 256) };
        cmsAppendNamedColor(namedColorList, name, PCS, colorant);
    }

    // Call the function-under-test
    cmsUInt32Number colorCount = cmsNamedColorCount(namedColorList);

    // Clean up
    cmsFreeNamedColorList(namedColorList);
    cmsDeleteContext(contextID);

    return 0;
}