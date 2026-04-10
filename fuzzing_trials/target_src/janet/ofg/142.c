#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern int32_t janet_optnat(const Janet *argv, int32_t n, int32_t def, int32_t max);

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract necessary parameters
    if (size < sizeof(Janet) + 3 * sizeof(int32_t)) {
        return 0;
    }

    // Extract parameters from the input data
    const Janet *argv = (const Janet *)data;
    int32_t n = *((int32_t *)(data + sizeof(Janet)));
    int32_t def = *((int32_t *)(data + sizeof(Janet) + sizeof(int32_t)));
    int32_t max = *((int32_t *)(data + sizeof(Janet) + 2 * sizeof(int32_t)));

    // Ensure n is within a valid range to prevent out-of-bounds access
    if (n < 0 || n >= size / sizeof(Janet)) {
        return 0;
    }

    // Ensure def and max are within a sensible range
    if (def < 0 || max < 0 || def > max) {
        return 0;
    }

    // Call the function-under-test
    int32_t result = janet_optnat(argv, n, def, max);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}