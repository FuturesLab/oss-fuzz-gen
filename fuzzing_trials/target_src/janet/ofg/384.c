#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_384(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract the required integers
    if (size < sizeof(int32_t) * 3) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Prepare the Janet array from the input data
    Janet *janet_array = (Janet *)janet_malloc(sizeof(Janet) * size);
    for (size_t i = 0; i < size; i++) {
        janet_array[i] = janet_wrap_integer(data[i]);
    }

    // Extract integers from the input data
    int32_t arg1 = (int32_t)data[0];
    int32_t arg2 = (int32_t)data[1];
    int32_t arg3 = (int32_t)data[2];

    // Call the function-under-test
    JanetBuffer *buffer = janet_optbuffer(janet_array, arg1, arg2, arg3);

    // Clean up
    janet_free(janet_array);
    janet_deinit();

    return 0;
}