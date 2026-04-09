#include <stdint.h>
#include <stddef.h>

// Assume the function is defined elsewhere
void janet_sandbox_assert(uint32_t value);

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to form a uint32_t
    }

    // Extract a uint32_t value from the input data
    uint32_t value = *(const uint32_t *)data;

    // Call the function-under-test
    janet_sandbox_assert(value);

    return 0;
}