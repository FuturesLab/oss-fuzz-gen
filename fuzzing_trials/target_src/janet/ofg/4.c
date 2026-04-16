#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    Janet janet_value;

    // Initialize Janet library
    janet_init();

    // Check if size is sufficient to create a Janet value
    if (size >= sizeof(Janet)) {
        // Copy the data into the Janet value
        memcpy(&janet_value, data, sizeof(Janet));

        // Call the function-under-test
        janet_checksize(janet_value);
    }

    // Deinitialize Janet library
    janet_deinit();

    return 0;
}