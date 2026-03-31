#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "/src/libhtp/htp/bstr.h" // Correct path for bstr.h

extern int bstr_cmp_c_nocase(const struct bstr_t *, const char *);

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to proceed
    }

    // Split the input data into two parts
    size_t bstr_len = size / 2;
    size_t char_len = size - bstr_len;

    // Create and initialize a bstr_t object
    struct bstr_t bstr_obj;
    bstr_obj.len = bstr_len;
    bstr_obj.size = bstr_len;
    bstr_obj.realptr = (unsigned char *)data;

    // Create and initialize a char array
    char *char_str = (char *)malloc(char_len + 1);
    if (char_str == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(char_str, data + bstr_len, char_len);
    char_str[char_len] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int result = bstr_cmp_c_nocase(&bstr_obj, char_str);

    // Clean up
    free(char_str);

    return 0;
}