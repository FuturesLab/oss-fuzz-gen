#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Assume the function bstr_util_cmp_mem_nocase is declared in some header file
// Include the relevant header file for the function declaration if available
int bstr_util_cmp_mem_nocase(const void *s1, size_t n1, const void *s2, size_t n2);

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to split into two non-empty parts
    }

    // Split the input data into two parts
    size_t mid = size / 2;
    const void *part1 = data;
    size_t size1 = mid;
    const void *part2 = data + mid;
    size_t size2 = size - mid;

    // Call the function-under-test
    int result = bstr_util_cmp_mem_nocase(part1, size1, part2, size2);

    // Use the result to prevent the compiler from optimizing away the call
    (void)result;

    return 0;
}