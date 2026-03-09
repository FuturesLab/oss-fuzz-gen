#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    // Assuming the function is declared in some header file
    int aom_uleb_encode_fixed_size(uint64_t value, size_t available, size_t fixed_size, uint8_t *buffer, size_t *encoded_size);
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize variables
    uint64_t value = 0;
    size_t available = 0;
    size_t fixed_size = 0;
    uint8_t buffer[256]; // A buffer to hold encoded data
    size_t encoded_size = 0;

    // Ensure data is large enough to extract values
    if (size < sizeof(uint64_t) + 2 * sizeof(size_t)) {
        return 0;
    }

    // Extract values from data
    std::memcpy(&value, data, sizeof(uint64_t));
    std::memcpy(&available, data + sizeof(uint64_t), sizeof(size_t));
    std::memcpy(&fixed_size, data + sizeof(uint64_t) + sizeof(size_t), sizeof(size_t));

    // Call the function-under-test
    aom_uleb_encode_fixed_size(value, available, fixed_size, buffer, &encoded_size);

    return 0;
}