#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h" // Assuming this is the library where Janet and janet_symeq are defined

int LLVMFuzzerTestOneInput_1480(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize the Janet environment (this is necessary for Janet functions to work correctly)
    janet_init();

    // Create a Janet object from the data
    Janet janet_obj;
    if (size >= sizeof(int32_t)) {
        // Use the first four bytes to create an integer Janet object
        int32_t value;
        memcpy(&value, data, sizeof(int32_t));
        janet_obj = janet_wrap_integer(value);
    } else {
        // Default to wrapping a single byte if not enough data
        janet_obj = janet_wrap_integer(data[0]);
    }

    // Create a null-terminated string from the remaining data
    // Ensure that the string creation does not exceed the input size
    size_t str_size = size > sizeof(int32_t) ? size - sizeof(int32_t) : 0;
    char str[str_size + 1];
    if (str_size > 0) {
        memcpy(str, data + sizeof(int32_t), str_size);
    }
    str[str_size] = '\0';

    // Call the function under test with non-null inputs
    // Ensure that janet_symeq is called with valid Janet objects
    Janet str_janet_obj = janet_cstringv(str);

    if (janet_checktype(janet_obj, JANET_NUMBER) && janet_checktype(str_janet_obj, JANET_STRING)) {
        janet_symeq(janet_obj, janet_unwrap_string(str_janet_obj));
    }

    // Deinitialize the Janet environment after use
    janet_deinit();

    return 0;
}