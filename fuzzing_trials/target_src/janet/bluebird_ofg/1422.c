#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "janet.h"  // Assuming the Janet library provides this header

int LLVMFuzzerTestOneInput_1422(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to contain at least one character for the string
    if (size < 1) {
        return 0;
    }

    // Initialize the Janet library if necessary
    janet_init();

    // Create a null-terminated string from the input data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0; // If memory allocation fails, return
    }
    memcpy(str, data, size);
    str[size] = '\0';

    // Create a Janet object
    Janet janet_obj;
    // Initialize the Janet object with some data
    JanetString janet_str = janet_string(data, size);
    if (janet_str == NULL) {
        free(str);
        return 0; // If string creation fails, clean up and return
    }
    janet_obj = janet_wrap_string(janet_str);

    // Call the function-under-test
    int result = janet_keyeq(janet_obj, str);

    // Clean up
    free(str);

    // Deinitialize the Janet library if necessary
    janet_deinit();

    return 0;
}