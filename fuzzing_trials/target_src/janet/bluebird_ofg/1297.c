#include <stdint.h>
#include <stddef.h>
#include "janet.h"

extern uint32_t janet_optuinteger(const Janet *argv, int32_t n, int32_t def, uint32_t fallback);

int LLVMFuzzerTestOneInput_1297(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t) * 2 + sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    // Initialize Janet array
    Janet argv[1];
    argv[0] = janet_wrap_integer((int32_t)data[0]);

    // Extract parameters from data
    int32_t n = (int32_t)data[1];
    int32_t def = (int32_t)data[2];
    uint32_t fallback = (uint32_t)data[3];

    // Call the function-under-test
    uint32_t result = janet_optuinteger(argv, n, def, fallback);

    // Use the result in some way to avoid compiler optimizations
    if (result == 0xFFFFFFFF) {
        return 1;
    }

    return 0;
}