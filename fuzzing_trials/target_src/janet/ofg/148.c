#include <stdint.h>
#include <stddef.h>

// Function-under-test
void janet_sandbox_assert(uint32_t value);

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Convert the first 4 bytes of data to a uint32_t
    uint32_t value = *((uint32_t *)data);

    // Call the function-under-test with the extracted value
    janet_sandbox_assert(value);

    return 0;
}