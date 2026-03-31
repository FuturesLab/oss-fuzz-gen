#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Function signature for the function-under-test
int bstr_util_cmp_mem(const void *a, size_t a_len, const void *b, size_t b_len);

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Split the input data into two parts for comparison
    size_t half_size = size / 2;
    const void *part_a = data;
    const void *part_b = data + half_size;

    // Ensure both parts have non-zero length
    size_t len_a = half_size;
    size_t len_b = size - half_size;

    // Call the function-under-test
    int result = bstr_util_cmp_mem(part_a, len_a, part_b, len_b);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}