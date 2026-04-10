#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Ensure size is sufficient for Janet data
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj = janet_wrap_number((double)data[0]);

    // Call the function-under-test
    if (janet_checktype(janet_obj, JANET_NUMBER)) {
        // Example operation on the Janet object
        double number = janet_unwrap_number(janet_obj);
        // Use the number as needed in the test
    }

    // Clean up Janet VM
    janet_deinit();

    return 0;
}