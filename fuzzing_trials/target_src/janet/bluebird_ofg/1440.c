#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1440(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Ensure the size is sufficient to extract at least one Janet value
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet value from the input data
    Janet key = janet_wrap_integer(data[0]);

    // Create a Janet structure with at least one element
    JanetKV *kv_array = janet_struct_begin(1);
    kv_array[0].key = janet_wrap_nil();
    kv_array[0].value = janet_wrap_nil();
    JanetStruct janet_struct = janet_struct_end(kv_array);

    // Call the function-under-test
    Janet result = janet_struct_rawget(janet_struct, key);

    // Clean up the Janet runtime
    janet_deinit();

    return 0;
}