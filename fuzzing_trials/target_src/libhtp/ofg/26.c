#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>  // Include for malloc and free

// Function-under-test declaration
int bstr_util_mem_index_of_c(const void *haystack, size_t haystack_len, const char *needle);

// Fuzzing harness
int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to contain both haystack and needle
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts: haystack and needle
    size_t haystack_len = size / 2;
    const void *haystack = (const void *)data;
    const char *needle = (const char *)(data + haystack_len);

    // Ensure that needle is null-terminated
    size_t needle_len = size - haystack_len;
    char *null_terminated_needle = (char *)malloc(needle_len + 1);
    if (!null_terminated_needle) {
        return 0;
    }
    memcpy(null_terminated_needle, needle, needle_len);
    null_terminated_needle[needle_len] = '\0';

    // Call the function-under-test
    int result = bstr_util_mem_index_of_c(haystack, haystack_len, null_terminated_needle);

    // Clean up
    free(null_terminated_needle);

    return 0;
}