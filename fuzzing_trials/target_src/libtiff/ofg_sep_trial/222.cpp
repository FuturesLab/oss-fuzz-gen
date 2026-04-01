#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the necessary header for memcpy

// Assuming the function is defined in an external C library
extern "C" {
    int uv_encode(double u, double v, int option);
}

extern "C" int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    if (size < sizeof(double) * 2 + sizeof(int)) {
        return 0; // Not enough data to extract two doubles and an int
    }

    double u, v;
    int option;

    // Copy bytes from data into u, v, and option
    memcpy(&u, data, sizeof(double));
    memcpy(&v, data + sizeof(double), sizeof(double));
    memcpy(&option, data + sizeof(double) * 2, sizeof(int));

    // Call the function under test
    uv_encode(u, v, option);

    return 0;
}