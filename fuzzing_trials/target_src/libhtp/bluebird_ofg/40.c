#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/bstr.h"  // Correct path to the bstr.h file

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to create two bstr objects
    }

    // Split the input data into two parts for two bstr objects
    size_t half_size = size / 2;
    size_t other_half_size = size - half_size;

    // Allocate and initialize the first bstr object
    struct bstr_t str1;  // Use 'struct' keyword to define bstr_t
    str1.realptr = (unsigned char *)malloc(half_size + 1);
    if (str1.realptr == NULL) {
        return 0; // Allocation failed
    }
    memcpy(str1.realptr, data, half_size);
    str1.realptr[half_size] = '\0'; // Ensure null-termination
    str1.len = half_size;
    str1.size = half_size + 1;

    // Allocate and initialize the second bstr object
    struct bstr_t str2;  // Use 'struct' keyword to define bstr_t
    str2.realptr = (unsigned char *)malloc(other_half_size + 1);
    if (str2.realptr == NULL) {
        free(str1.realptr);
        return 0; // Allocation failed
    }
    memcpy(str2.realptr, data + half_size, other_half_size);
    str2.realptr[other_half_size] = '\0'; // Ensure null-termination
    str2.len = other_half_size;
    str2.size = other_half_size + 1;

    // Call the function-under-test
    int result = bstr_index_of_nocase(&str1, &str2);

    // Free allocated memory
    free(str1.realptr);
    free(str2.realptr);

    return 0;
}