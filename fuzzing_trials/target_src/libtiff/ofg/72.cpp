#include <cstddef>
#include <cstdint>
#include <iostream>

extern "C" {
    // Assuming the function is defined in some C library
    int uv_decode(double *u, double *v, int option);
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    if (size < sizeof(double) * 2 + sizeof(int)) {
        // Not enough data to fill the parameters
        return 0;
    }

    // Initialize parameters
    double u = 0.0;
    double v = 0.0;
    int option = 0;

    // Copy data into the parameters
    std::memcpy(&u, data, sizeof(double));
    std::memcpy(&v, data + sizeof(double), sizeof(double));
    std::memcpy(&option, data + 2 * sizeof(double), sizeof(int));

    // Call the function-under-test
    int result = uv_decode(&u, &v, option);

    // Print the result for debugging purposes
    std::cout << "uv_decode result: " << result << std::endl;

    return 0;
}