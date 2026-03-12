#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract the required parameters
    if (size < sizeof(double) * 4 + sizeof(cmsCIELab)) {
        return 0;
    }

    // Initialize the cmsCIELab structure
    cmsCIELab lab;
    lab.L = (double)data[0]; // Using the first byte for L
    lab.a = (double)data[1]; // Using the second byte for a
    lab.b = (double)data[2]; // Using the third byte for b

    // Extract double values from the data
    double d1 = *(double*)(data + 3);
    double d2 = *(double*)(data + 3 + sizeof(double));
    double d3 = *(double*)(data + 3 + 2 * sizeof(double));
    double d4 = *(double*)(data + 3 + 3 * sizeof(double));

    // Call the function under test
    cmsBool result = cmsDesaturateLab(&lab, d1, d2, d3, d4);

    // Use the result to prevent it from being optimized out
    (void)result;

    return 0;
}