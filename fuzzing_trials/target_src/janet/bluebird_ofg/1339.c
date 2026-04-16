#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1339(const uint8_t *data, size_t size) {
    // Initialize Janet if not already initialized
    janet_init();

    // Create a Janet object from the input data
    Janet janet_obj;
    if (size >= sizeof(Janet)) {
        janet_obj = *(Janet *)data;
    } else {
        // If size is smaller than a Janet object, fill with default values
        janet_obj = janet_wrap_nil();
    }

    // Call the function-under-test
    int result = janet_gcunrootall(janet_obj);

    // Clean up Janet resources
    janet_deinit();

    return 0;
}