#include "janet.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_1511(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure the input size is sufficient to create a JanetKV
    if (size < sizeof(JanetKV)) {
        janet_deinit();
        return 0;
    }

    // Allocate memory for JanetKV
    JanetKV *kv = (JanetKV *)malloc(sizeof(JanetKV));
    if (!kv) {
        janet_deinit();
        return 0; // Check for malloc failure
    }

    // Initialize JanetKV with the first part of the data
    memcpy(kv, data, sizeof(JanetKV));

    // Create a Janet value from the remaining data
    Janet janet_value;
    if (size > sizeof(JanetKV)) {
        janet_value = janet_wrap_number((double)data[sizeof(JanetKV)]);
    } else {
        janet_value = janet_wrap_nil();
    }

    // Create a JanetStruct from the JanetKV
    JanetStruct jstruct = janet_struct_begin(1);
    janet_struct_put(jstruct, janet_wrap_nil(), janet_value);
    JanetStruct finalized_struct = janet_struct_end(jstruct);

    // Call the function-under-test
    Janet result = janet_struct_get(finalized_struct, janet_wrap_nil());

    // Clean up
    free(kv);
    janet_deinit();

    return 0;
}