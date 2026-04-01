#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Function-under-test declaration
int bstr_util_mem_index_of_c_nocase(const void *haystack, size_t haystack_len, const char *needle);

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to split into haystack and needle
    if (size < 2) {
        return 0;
    }

    // Split the input data into haystack and needle
    size_t haystack_len = size / 2;
    const void *haystack = (const void *)data;
    const char *needle = (const char *)(data + haystack_len);

    // Ensure the needle is null-terminated
    char *null_terminated_needle = (char *)malloc(haystack_len + 1);
    if (null_terminated_needle == NULL) {
        return 0;
    }
    memcpy(null_terminated_needle, needle, haystack_len);
    null_terminated_needle[haystack_len] = '\0';

    // Call the function-under-test
    int result = bstr_util_mem_index_of_c_nocase(haystack, haystack_len, null_terminated_needle);

    // Clean up
    free(null_terminated_needle);

    return 0;
}