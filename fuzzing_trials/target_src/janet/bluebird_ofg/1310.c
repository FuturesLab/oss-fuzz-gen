#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

// The function under test expects a JanetStruct
extern JanetTable *janet_struct_to_table(JanetStruct st);

int LLVMFuzzerTestOneInput_1310(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure there is enough data to create at least one JanetKV
    if (size < sizeof(JanetKV)) {
        janet_deinit();
        return 0;
    }

    // Calculate the number of JanetKV elements we can create
    int32_t num_elements = size / sizeof(JanetKV);

    // Allocate memory for a JanetKV array
    JanetKV *kv_array = (JanetKV *)malloc(num_elements * sizeof(JanetKV));
    if (!kv_array) {
        janet_deinit();
        return 0;
    }

    // Copy data into the JanetKV array
    for (int32_t i = 0; i < num_elements; i++) {
        kv_array[i].key = janet_wrap_integer((int32_t)data[i % size]);
        kv_array[i].value = janet_wrap_integer((int32_t)data[(i + 1) % size]);
    }

    // Create a JanetStruct from the kv_array
    JanetStruct janet_struct = janet_struct_begin(num_elements);
    for (int32_t i = 0; i < num_elements; i++) {
        janet_struct_put(janet_struct, kv_array[i].key, kv_array[i].value);
    }
    janet_struct = janet_struct_end(janet_struct);

    // Call the function-under-test with the JanetStruct
    JanetTable *table = janet_struct_to_table(janet_struct);

    // Clean up
    free(kv_array);

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}