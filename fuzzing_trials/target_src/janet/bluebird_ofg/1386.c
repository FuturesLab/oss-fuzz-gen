#include <stdint.h>
#include <stddef.h>
#include "janet.h"
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_1386(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a JanetKeyword
    if (size < 1) {
        return 0;
    }

    // Initialize the Janet runtime before using Janet functions
    janet_init();

    // Create a null-terminated string from the input data
    char *keyword_str = (char *)malloc(size + 1);
    if (!keyword_str) {
        janet_deinit(); // Deinitialize if memory allocation fails
        return 0;
    }
    memcpy(keyword_str, data, size);
    keyword_str[size] = '\0'; // Null-terminate the string

    // JanetKeyword requires a string and its length, ensure it's not empty
    // Use janet_csymbol to ensure the keyword is valid
    JanetKeyword keyword = janet_csymbol(keyword_str);

    // Call the function-under-test
    Janet result = janet_wrap_keyword(keyword);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    // Deinitialize the Janet runtime to clean up resources
    janet_deinit();

    // Free the allocated memory
    free(keyword_str);

    return 0;
}