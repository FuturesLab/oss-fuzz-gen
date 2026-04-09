#include <stdint.h>
#include <stddef.h>
#include "janet.h"

extern int32_t janet_optnat(const Janet *argv, int32_t n, int32_t def, int32_t max);

int LLVMFuzzerTestOneInput_1296(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + 2 * sizeof(int32_t)) {
        return 0;
    }

    Janet argv[1];
    int32_t n, def, max;

    // Initialize Janet value from data
    janet_init();
    argv[0] = janet_wrap_integer((int32_t)data[0]);

    // Extract n, def, and max from data
    n = (int32_t)data[1];
    def = (int32_t)data[2];
    max = (int32_t)data[3];

    // Call the function-under-test
    int32_t result = janet_optnat(argv, n, def, max);

    // Cleanup Janet
    janet_deinit();

    return 0;
}