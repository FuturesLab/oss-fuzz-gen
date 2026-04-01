#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "/src/libhtp/htp/bstr.h"  // Correct path to the bstr.h header

// Function-under-test
int bstr_index_of_c_nocasenorzero(const bstr *b, const char *str);

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to create two non-empty strings
    }

    // Split the input data into two parts for bstr and char*
    size_t split_index = size / 2;

    // Initialize bstr
    bstr b;
    b.len = split_index;
    b.size = split_index + 1; // Allocate space for null-termination
    b.realptr = (unsigned char *)malloc(b.size);
    if (b.realptr == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(b.realptr, data, b.len);
    b.realptr[b.len] = '\0'; // Null-terminate the bstr data

    // Initialize char* string
    size_t str_len = size - split_index;
    char *str = (char *)malloc(str_len + 1);
    if (str == NULL) {
        free(b.realptr);
        return 0; // Memory allocation failed
    }
    memcpy(str, data + split_index, str_len);
    str[str_len] = '\0'; // Null-terminate the char* string

    // Call the function-under-test
    int result = bstr_index_of_c_nocasenorzero(&b, str);

    // Cleanup
    free(b.realptr);
    free(str);

    return 0;
}