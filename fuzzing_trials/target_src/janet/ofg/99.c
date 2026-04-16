#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    if (size < sizeof(Janet) + 3 * sizeof(int32_t)) {
        janet_deinit();
        return 0; // Ensure there is enough data for the inputs
    }

    // Initialize Janet array from the input data
    const Janet *janet_array = (const Janet *)data;

    // Extract int32_t values from the data
    int32_t arg1 = *(const int32_t *)(data + sizeof(Janet));
    int32_t arg2 = *(const int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    int32_t arg3 = *(const int32_t *)(data + sizeof(Janet) + 2 * sizeof(int32_t));

    // Ensure the Janet array is valid
    if (!janet_checktype(*janet_array, JANET_ARRAY)) {
        janet_deinit();
        return 0;
    }

    // Call the function-under-test
    int32_t result = janet_getendrange(janet_array, arg1, arg2, arg3);

    // Use the result to avoid compiler optimizations
    (void)result;

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}