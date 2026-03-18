#include <cstdint>
#include <cstddef>
#include <aom/aom_integer.h>  // Include the necessary header for aom_uleb_size_in_bytes

extern "C" {
    // Declare the function-under-test
    size_t aom_uleb_size_in_bytes(uint64_t value);
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    uint64_t value = 0;

    // Ensure that the size is at least 8 bytes to read a uint64_t
    if (size >= sizeof(uint64_t)) {
        // Copy the first 8 bytes of data into the uint64_t value
        value = *reinterpret_cast<const uint64_t*>(data);
    }

    // Call the function-under-test
    size_t result = aom_uleb_size_in_bytes(value);

    // Use the result in some way to prevent the compiler from optimizing it away
    (void)result;

    return 0;
}