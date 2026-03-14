#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy
#include <lcms2.h> // Include the Little CMS library header

// Define a function to convert bytes to a double in a safe way
static double bytes_to_double(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) return 0.0;
    double value;
    memcpy(&value, data, sizeof(double));
    return value;
}

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size < 6 * sizeof(double)) {
        return 0; // Ensure there is enough data for two cmsCIELab structures
    }

    // Initialize two cmsCIELab structures
    cmsCIELab Lab1, Lab2;

    // Populate Lab1 with data
    Lab1.L = bytes_to_double(data, size);
    Lab1.a = bytes_to_double(data + sizeof(double), size - sizeof(double));
    Lab1.b = bytes_to_double(data + 2 * sizeof(double), size - 2 * sizeof(double));

    // Populate Lab2 with data
    Lab2.L = bytes_to_double(data + 3 * sizeof(double), size - 3 * sizeof(double));
    Lab2.a = bytes_to_double(data + 4 * sizeof(double), size - 4 * sizeof(double));
    Lab2.b = bytes_to_double(data + 5 * sizeof(double), size - 5 * sizeof(double));

    // Call the function under test
    cmsFloat64Number deltaE = cmsCIE94DeltaE(&Lab1, &Lab2);

    // Use the result to prevent the compiler from optimizing the function call away
    volatile cmsFloat64Number result = deltaE;
    (void)result;

    return 0;
}