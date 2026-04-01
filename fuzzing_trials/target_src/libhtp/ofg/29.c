#include <stddef.h>
#include <stdint.h>

extern int bstr_util_mem_index_of_mem(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len);

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Ensure there is enough data to split into haystack and needle
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts: haystack and needle
    size_t haystack_len = size / 2;
    size_t needle_len = size - haystack_len;

    const void *haystack = (const void *)data;
    const void *needle = (const void *)(data + haystack_len);

    // Call the function-under-test
    bstr_util_mem_index_of_mem(haystack, haystack_len, needle, needle_len);

    return 0;
}