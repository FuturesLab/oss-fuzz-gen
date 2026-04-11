#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <janet.h>  // Assuming Janet library provides this header

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract meaningful inputs
    if (size < sizeof(Janet) + sizeof(int32_t) + 1) {
        return 0;
    }

    // Initialize Janet array
    Janet janet_array[1];
    memcpy(janet_array, data, sizeof(Janet));

    // Validate the Janet value
    if (!janet_checktype(janet_array[0], JANET_ARRAY) && 
        !janet_checktype(janet_array[0], JANET_STRING) &&
        !janet_checktype(janet_array[0], JANET_SYMBOL) &&
        !janet_checktype(janet_array[0], JANET_KEYWORD)) {
        return 0;
    }

    // Extract int32_t value
    int32_t index;
    memcpy(&index, data + sizeof(Janet), sizeof(int32_t));

    // Ensure index is within a reasonable range
    if (index < 0 || index >= 1024) {  // Assuming 1024 is a reasonable upper limit
        return 0;
    }

    // Extract a string from the remaining data
    const char *str = (const char *)(data + sizeof(Janet) + sizeof(int32_t));
    size_t str_len = size - sizeof(Janet) - sizeof(int32_t);
    
    // Ensure the string is null-terminated
    char *cstr = (char *)malloc(str_len + 1);
    if (!cstr) {
        return 0;
    }
    memcpy(cstr, str, str_len);
    cstr[str_len] = '\0';

    // Call the function-under-test
    uint64_t flags = janet_getflags(janet_array, index, cstr);

    // Clean up
    free(cstr);

    return 0;
}