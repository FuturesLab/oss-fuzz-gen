#include <cstdint>
#include <cstddef>
#include <cstring>  // Include this header for std::memcpy
#include <tiffio.h>

extern "C" {
    void TIFFSwabDouble(double *value);
}

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0; // Not enough data to form a double
    }

    // Create a double variable from the input data
    double input_value;
    std::memcpy(&input_value, data, sizeof(double));

    // Call the function-under-test
    TIFFSwabDouble(&input_value);

    return 0;
}