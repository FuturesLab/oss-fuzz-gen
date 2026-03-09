#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

// Assume the function aom_uleb_decode is defined in an external C library
extern "C" {
    int aom_uleb_decode(const uint8_t *buffer, size_t buffer_size, uint64_t *value, size_t *length);
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    uint64_t value = 0;
    size_t length = 0;

    // Call the function-under-test
    int result = aom_uleb_decode(data, size, &value, &length);

    // Optionally print result for debugging purposes
    std::cout << "Result: " << result << ", Value: " << value << ", Length: " << length << std::endl;

    return 0;
}