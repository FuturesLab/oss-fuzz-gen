#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_439(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number rows = 2; // Example value, adjust as needed
    cmsUInt32Number cols = 2; // Example value, adjust as needed

    // Ensure that the size of data is sufficient for the matrix and offset arrays
    if (size < (rows * cols + cols) * sizeof(cmsFloat64Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Allocate and initialize matrix and offset arrays
    const cmsFloat64Number* matrix = (const cmsFloat64Number*) data;
    const cmsFloat64Number* offset = (const cmsFloat64Number*) (data + rows * cols * sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsStage* stage = cmsStageAllocMatrix(context, rows, cols, matrix, offset);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    cmsDeleteContext(context);

    return 0;
}