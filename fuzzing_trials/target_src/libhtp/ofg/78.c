#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h> // Optional, for debugging purposes

// Assume the function-under-test is declared in a header file
int bstr_util_mem_index_of_mem_nocase(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len);

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Split the input data into two parts: haystack and needle
    const size_t min_size = 1; // Minimum size for haystack and needle
    if (size < 2 * min_size) {
        return 0; // Not enough data to split into two parts
    }

    size_t haystack_len = size / 2;
    size_t needle_len = size - haystack_len;

    const void *haystack = (const void *)data;
    const void *needle = (const void *)(data + haystack_len);

    // Call the function-under-test
    int result = bstr_util_mem_index_of_mem_nocase(haystack, haystack_len, needle, needle_len);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}