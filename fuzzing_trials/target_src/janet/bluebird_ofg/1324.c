#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1324(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure there is enough data to create a JanetStruct
    if (size < sizeof(JanetKV)) {
        janet_deinit();
        return 0;
    }

    // Create a JanetKV array from the input data
    JanetKV *kvs = (JanetKV *)data;
    size_t kv_count = size / sizeof(JanetKV);

    // Create a JanetKV array for janet_struct_end
    JanetKV *janet_kv_array = janet_struct_begin(kv_count);
    for (size_t i = 0; i < kv_count; i++) {
        janet_kv_array[i] = kvs[i];
    }
    JanetStruct janet_struct = janet_struct_end(janet_kv_array);

    // Call the function-under-test
    Janet result = janet_wrap_struct(janet_struct);

    // Use the result to prevent compiler optimizations from removing the call
    (void)result;

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}