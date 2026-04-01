#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Assuming the function is declared somewhere
int bstr_util_cmp_mem_nocase(const void *s1, size_t n1, const void *s2, size_t n2);

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Split the input data into two parts for comparison
    size_t half_size = size / 2;
    const void *s1 = data;
    const void *s2 = data + half_size;

    // Ensure that both halves have at least one byte to compare
    size_t n1 = (half_size > 0) ? half_size : 1;
    size_t n2 = (size - half_size > 0) ? size - half_size : 1;

    // Call the function under test
    int result = bstr_util_cmp_mem_nocase(s1, n1, s2, n2);

    // Return 0 to indicate successful execution
    return 0;
}