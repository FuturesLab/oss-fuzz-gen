#include <stdint.h>
#include <stddef.h>
#include "janet.h"

// Initialize a Janet structure with some values
static JanetKV *initialize_janet_kv() {
    JanetKV *kv = janet_struct_begin(10);
    for (int i = 0; i < 10; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(i * 10);
        janet_struct_put(kv, key, value);
    }
    return kv;
}

int LLVMFuzzerTestOneInput_1518(const uint8_t *data, size_t size) {
    if (size < 2 * sizeof(int32_t)) {
        return 0;
    }

    // Ensure the Janet environment is properly initialized
    janet_init();

    // Initialize a Janet structure
    JanetKV *kv = initialize_janet_kv();

    // Use the data to create Janet key and value
    int32_t key_int = *(int32_t *)data;
    int32_t value_int = *(int32_t *)(data + sizeof(int32_t));

    Janet key = janet_wrap_integer(key_int);
    Janet value = janet_wrap_integer(value_int);

    // Call the function-under-test
    janet_struct_put(kv, key, value);

    // Clean up
    janet_struct_end(kv);

    // Finalize the Janet environment
    janet_deinit();

    return 0;
}