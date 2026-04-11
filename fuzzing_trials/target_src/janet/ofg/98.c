#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h>

// Ensure that the Janet environment is initialized before using any Janet functions
static void initialize_janet_98() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

extern int32_t janet_getendrange(const Janet *, int32_t, int32_t, int32_t);

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    initialize_janet_98();

    if (size < sizeof(Janet) + 3 * sizeof(int32_t)) {
        return 0;
    }

    // Initialize the Janet pointer from the input data
    Janet janet_value;
    // Properly initialize the Janet value to avoid using uninitialized memory
    janet_value = janet_wrap_nil(); // Assuming a default initialization to nil

    // Copy the data into the Janet value only if sufficient data is available
    memcpy(&janet_value, data, sizeof(Janet));
    const Janet *janet_ptr = &janet_value;

    // Ensure the Janet value is a valid type that can be used with janet_getendrange
    if (!janet_checktype(janet_value, JANET_ARRAY) && !janet_checktype(janet_value, JANET_STRING)) {
        return 0;
    }

    // Extract int32_t values from the input data
    int32_t index = *(const int32_t *)(data + sizeof(Janet));
    int32_t offset = *(const int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    int32_t length = *(const int32_t *)(data + sizeof(Janet) + 2 * sizeof(int32_t));

    // Call the function-under-test
    int32_t result = janet_getendrange(janet_ptr, index, offset, length);

    // Use the result in some way to avoid any compiler optimizations removing the call
    (void)result;

    return 0;
}