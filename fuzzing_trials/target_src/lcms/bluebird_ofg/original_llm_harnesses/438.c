#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_438(const uint8_t *data, size_t size) {
    if (size < 9) {
        // Ensure there is enough data to fill the matrix and offset arrays
        return 0;
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number rows = 3; // Example value for rows
    cmsUInt32Number cols = 3; // Example value for columns

    // Allocate memory for the matrix and offset arrays
    cmsFloat64Number matrix[rows * cols];
    cmsFloat64Number offset[rows];

    // Initialize matrix and offset with values from the input data
    for (cmsUInt32Number i = 0; i < rows * cols; i++) {
        matrix[i] = (cmsFloat64Number)(data[i]) / 255.0;
    }
    for (cmsUInt32Number i = 0; i < rows; i++) {
        offset[i] = (cmsFloat64Number)(data[i + rows * cols]) / 255.0;
    }

    // Call the function under test
    cmsStage *stage = cmsStageAllocMatrix(context, rows, cols, matrix, offset);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }
    cmsDeleteContext(context);

    return 0;
}