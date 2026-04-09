#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern int janet_optboolean(const Janet *, int32_t, int32_t, int);

int LLVMFuzzerTestOneInput_398(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Prepare the Janet array from the input data
    const Janet *janet_array = (const Janet *)data;

    // Define the other parameters
    int32_t n = (size / sizeof(Janet)) - 1; // Ensure n is within bounds
    int32_t def = 0; // Default value
    int32_t index = 0; // Index to start from, ensure it's within bounds

    // Call the function-under-test
    int result = janet_optboolean(janet_array, n, index, def);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}