#include <cstdint>
#include <cstddef>
#include <cmath>

extern "C" {
    // Declaration of the function-under-test
    int uv_encode(double u, double v, int precision);
}

extern "C" int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    if (size < sizeof(double) * 2 + sizeof(int)) {
        return 0; // Not enough data to extract two doubles and an int
    }

    // Extract two doubles and an int from the input data
    double u = *reinterpret_cast<const double*>(data);
    double v = *reinterpret_cast<const double*>(data + sizeof(double));
    int precision = *reinterpret_cast<const int*>(data + sizeof(double) * 2);

    // Ensure precision is within a reasonable range
    precision = std::abs(precision) % 100; // Example range limit for precision

    // Call the function-under-test
    uv_encode(u, v, precision);

    return 0;
}