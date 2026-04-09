#include <stdint.h>
#include <stddef.h>
#include <janet.h> // Include the Janet library header

// Function prototype for the function-under-test
void janet_put(Janet key, Janet value, Janet table);

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create at least three Janet values
    if (size < 3 * sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create three Janet values from the input data
    Janet key = janet_wrap_integer((int32_t)data[0]);
    Janet value = janet_wrap_integer((int32_t)data[1]);
    Janet table = janet_wrap_table(janet_table(0));

    // Call the function-under-test
    janet_put(key, value, table);

    // Clean up Janet
    janet_deinit();

    return 0;
}