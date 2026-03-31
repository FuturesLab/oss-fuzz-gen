#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Function-under-test declaration
int bstr_util_mem_index_of_mem_nocase(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len);

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to split into two non-empty parts
    if (size < 2) {
        return 0;
    }

    // Split the data into two parts: haystack and needle
    size_t haystack_len = size / 2;
    size_t needle_len = size - haystack_len;

    const void *haystack = (const void *)data;
    const void *needle = (const void *)(data + haystack_len);

    // Call the function-under-test
    int result = bstr_util_mem_index_of_mem_nocase(haystack, haystack_len, needle, needle_len);

    // Use the result in some way to avoid optimization issues
    (void)result;

    return 0;
}