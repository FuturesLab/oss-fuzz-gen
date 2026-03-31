#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

extern int bstr_util_mem_index_of_mem_nocasenorzero(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len);

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to split into two parts
    }

    // Split the input data into two parts
    size_t haystack_len = size / 2;
    size_t needle_len = size - haystack_len;

    // Ensure both lengths are non-zero
    if (haystack_len == 0 || needle_len == 0) {
        return 0;
    }

    // Assign the parts to haystack and needle
    const void *haystack = data;
    const void *needle = data + haystack_len;

    // Call the function under test
    bstr_util_mem_index_of_mem_nocasenorzero(haystack, haystack_len, needle, needle_len);

    return 0;
}