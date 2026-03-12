#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Check if there is enough data for meaningful input
    if (size < 12 + 32) { // 12 for pcs and device, 32 for colorName
        return 0;
    }

    // Initialize a valid CMS context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Allocate a named color list with a valid context
    cmsNAMEDCOLORLIST *namedColorList = cmsAllocNamedColorList(context, 1, 32, "prefix", "suffix");
    if (namedColorList == NULL) {
        cmsDeleteContext(context);
        return 0; // Exit if allocation fails
    }

    // Use the input data to set the color name
    char colorName[33];
    memcpy(colorName, data + 12, 32);
    colorName[32] = '\0'; // Ensure null termination

    // Use the input data to modify pcs and device arrays
    cmsUInt16Number pcs[3] = {
        data[0] | (data[1] << 8),
        data[2] | (data[3] << 8),
        data[4] | (data[5] << 8)
    };
    cmsUInt16Number device[3] = {
        data[6] | (data[7] << 8),
        data[8] | (data[9] << 8),
        data[10] | (data[11] << 8)
    };

    // Call the function-under-test
    cmsBool result = cmsAppendNamedColor(namedColorList, colorName, pcs, device);

    // Check the result to ensure the function is invoked correctly
    if (result == FALSE) {
        // Handle the error case if needed
    }

    // Clean up
    cmsFreeNamedColorList(namedColorList);
    cmsDeleteContext(context);

    return 0;
}