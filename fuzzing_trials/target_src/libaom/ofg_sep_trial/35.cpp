#include <cstdint>
#include <cstddef>
#include <cinttypes>
#include <iostream>

extern "C" {
    // Function-under-test
    int aom_uleb_decode(const uint8_t *data, size_t size, uint64_t *value, size_t *length);
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize output variables
    uint64_t value = 0;
    size_t length = 0;

    // Call the function-under-test
    int result = aom_uleb_decode(data, size, &value, &length);

    // Optionally print the results for debugging
    std::cout << "Result: " << result << ", Value: " << value << ", Length: " << length << std::endl;

    return 0;
}