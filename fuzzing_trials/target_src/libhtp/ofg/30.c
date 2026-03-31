#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Function-under-test declaration
int bstr_util_mem_index_of_mem(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len);

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into two non-empty parts
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts
    size_t haystack_len = size / 2;
    size_t needle_len = size - haystack_len;

    const void *haystack = data;
    const void *needle = data + haystack_len;

    // Call the function-under-test
    int result = bstr_util_mem_index_of_mem(haystack, haystack_len, needle, needle_len);

    // Use the result in some way to avoid any compiler optimizations
    (void)result;

    return 0;
}