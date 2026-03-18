#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t

extern "C" {
    // Assuming the function is declared in a header file
    int uv_decode(double *u, double *v, int option);
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters
    double u = 0.0;
    double v = 0.0;
    int option = 0;

    // Ensure the size is sufficient to extract meaningful data
    if (size >= sizeof(double) * 2 + sizeof(int)) {
        // Copy data into the parameters
        u = *reinterpret_cast<const double*>(data);
        v = *reinterpret_cast<const double*>(data + sizeof(double));
        option = *reinterpret_cast<const int*>(data + sizeof(double) * 2);
    }

    // Call the function-under-test
    uv_decode(&u, &v, option);

    return 0;
}