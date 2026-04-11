#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1387(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated to safely create a string
    char *keyword_str = (char *)malloc(size + 1);
    if (!keyword_str) {
        return 0;
    }
    memcpy(keyword_str, data, size);
    keyword_str[size] = '\0';

    // Initialize the Janet runtime
    janet_init();

    // Create a JanetKeyword from the input data
    Janet keyword = janet_ckeywordv(keyword_str);

    // Call the function-under-test
    Janet result = janet_wrap_keyword(janet_unwrap_keyword(keyword));

    // Clean up
    free(keyword_str);

    // Deinitialize the Janet runtime
    janet_deinit();

    return 0;
}