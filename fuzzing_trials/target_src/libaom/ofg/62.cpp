#include <cstdint>
#include <cstddef>
#include <cstring>

// Assuming the function is defined in an external C library
extern "C" {
    int aom_uleb_encode(uint64_t value, size_t available, uint8_t *buffer, size_t *encoded_size);
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a uint64_t and a size_t
    if (size < sizeof(uint64_t) + sizeof(size_t)) {
        return 0;
    }

    // Extract a uint64_t value from the input data
    uint64_t value;
    memcpy(&value, data, sizeof(uint64_t));

    // Extract a size_t value from the input data
    size_t available;
    memcpy(&available, data + sizeof(uint64_t), sizeof(size_t));

    // Ensure the buffer is not NULL and has some size
    uint8_t buffer[256]; // Fixed size buffer for simplicity
    size_t encoded_size = 0;

    // Call the function under test
    aom_uleb_encode(value, available, buffer, &encoded_size);

    return 0;
}