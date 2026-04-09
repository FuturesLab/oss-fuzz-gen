#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function-under-test
uint64_t janet_optuinteger64(const Janet *argv, int32_t n, int32_t argc, uint64_t def);

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to create a Janet array
    if (size < sizeof(Janet) * 2) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet array from the input data
    Janet argv[2];
    argv[0] = janet_wrap_integer((int32_t)data[0]);
    argv[1] = janet_wrap_integer((int32_t)data[1]);

    // Define n, argc, and def with non-null values
    int32_t n = 0;
    int32_t argc = 2;
    uint64_t def = 42;

    // Call the function-under-test
    uint64_t result = janet_optuinteger64(argv, n, argc, def);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}