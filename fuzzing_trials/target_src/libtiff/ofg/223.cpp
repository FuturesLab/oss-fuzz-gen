#include <cstdint>
#include <cstddef>
#include <cstring>  // Include for std::memcpy

extern "C" {
    // Function-under-test declaration
    int uv_encode(double u, double v, int flag);
}

extern "C" int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    if (size < sizeof(double) * 2 + sizeof(int)) {
        return 0;  // Not enough data to extract two doubles and an int
    }
    
    // Extract two doubles and an int from the input data
    double u, v;
    int flag;
    
    // Copy data into the variables
    std::memcpy(&u, data, sizeof(double));
    std::memcpy(&v, data + sizeof(double), sizeof(double));
    std::memcpy(&flag, data + sizeof(double) * 2, sizeof(int));
    
    // Call the function-under-test
    uv_encode(u, v, flag);
    
    return 0;
}