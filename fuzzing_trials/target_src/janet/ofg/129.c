#include <stdint.h>
#include <string.h> // Include for memcpy
#include <janet.h>  // Include for Janet types and functions

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Construct a Janet value from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Initialize the Janet environment if necessary
    janet_init();

    // Call the macro under test
    int result = janet_truthy(janet_value);

    // Use the result in some way to prevent any compiler optimizations
    // that might remove the call to janet_truthy
    (void)result;

    // Deinitialize the Janet environment if necessary
    janet_deinit();

    return 0;
}