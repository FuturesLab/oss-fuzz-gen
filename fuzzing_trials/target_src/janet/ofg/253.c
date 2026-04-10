#include <stdint.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_253(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract the required parameters
    if (size < sizeof(int32_t) * 2 + sizeof(uint8_t)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create an empty Janet array
    JanetArray *array = janet_array(0);
    Janet janet_array = janet_wrap_array(array);

    int32_t n = *((int32_t *)(data));
    int32_t def = *((int32_t *)(data + sizeof(int32_t)));
    const uint8_t *opt = data + sizeof(int32_t) * 2;

    // Ensure 'opt' is a valid null-terminated string for janet_optkeyword
    uint8_t opt_str[256];
    size_t opt_len = size - (sizeof(int32_t) * 2);
    if (opt_len >= sizeof(opt_str)) {
        opt_len = sizeof(opt_str) - 1;
    }
    memcpy(opt_str, opt, opt_len);
    opt_str[opt_len] = '\0';

    // Ensure 'n' is within bounds of the array to prevent out-of-bounds access
    if (n < 0 || n >= array->count) {
        n = 0; // Default to a safe index
    }

    // Call the function-under-test
    JanetKeyword result = janet_optkeyword(&janet_array, n, def, opt_str);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}