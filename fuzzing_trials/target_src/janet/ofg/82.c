#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a Janet object from the input data
    Janet janet_input;
    memcpy(&janet_input, data, sizeof(Janet));

    // Call the function-under-test
    JanetStruct result = janet_unwrap_struct(janet_input);

    // Clean up Janet
    janet_deinit();

    return 0;
}