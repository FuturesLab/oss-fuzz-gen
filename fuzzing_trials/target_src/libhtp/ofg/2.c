#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Function-under-test declaration
int bstr_util_mem_index_of_mem_nocasenorzero(const void *haystack, size_t haystack_len, const void *needle, size_t needle_len);

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Declare and initialize variables for haystack and needle
    const void *haystack = data;
    size_t haystack_len = size;

    // Ensure needle is not NULL and has a length greater than zero
    const void *needle = (size > 1) ? data + 1 : data;
    size_t needle_len = (size > 1) ? size - 1 : size;

    // Call the function-under-test
    int result = bstr_util_mem_index_of_mem_nocasenorzero(haystack, haystack_len, needle, needle_len);

    // Return 0 to indicate successful execution
    return 0;
}