#include <cstdint>
#include <cstddef>

// Assuming the function is defined in a C library
extern "C" {
    int uv_decode(double *u, double *v, int mode);
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two doubles and an int
    if (size < sizeof(double) * 2 + sizeof(int)) {
        return 0;
    }

    // Initialize the parameters
    double u = 0.0;
    double v = 0.0;
    int mode = 0;

    // Extract doubles and int from the input data
    u = *(reinterpret_cast<const double*>(data));
    v = *(reinterpret_cast<const double*>(data + sizeof(double)));
    mode = *(reinterpret_cast<const int*>(data + sizeof(double) * 2));

    // Call the function under test
    uv_decode(&u, &v, mode);

    return 0;
}