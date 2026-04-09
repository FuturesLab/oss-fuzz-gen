#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_396(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Declare and initialize Janet variables
    Janet janet1, janet2;

    // Ensure size is sufficient for two Janet values
    if (size < sizeof(Janet) * 2) {
        janet_deinit();
        return 0;
    }

    // Initialize the Janet values with data
    janet1 = janet_wrap_integer((int)data[0]); // Use first byte as integer
    janet2 = janet_wrap_integer((int)data[1]); // Use second byte as integer

    // Call the function-under-test
    Janet result = janet_next(janet1, janet2);

    // Clean up Janet runtime
    janet_deinit();

    // Return success
    return 0;
}