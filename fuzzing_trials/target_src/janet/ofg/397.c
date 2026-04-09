#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_397(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Prepare the Janet array
    const Janet *janet_array = (const Janet *)data;
    int32_t n = size / sizeof(Janet);

    // Define default values for the other parameters
    int32_t index = 0; // Start with the first element
    int32_t def = 0;   // Default index
    int def_value = 0; // Default boolean value

    // Call the function-under-test
    janet_optboolean(janet_array, n, index, def_value);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}