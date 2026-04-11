#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated for string operations
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Initialize hts_pos_t variables
    hts_pos_t beg = 0;
    hts_pos_t end = 0;

    // Call the function-under-test
    const char *result = hts_parse_reg64(input, &beg, &end);

    // Free allocated memory
    free(input);

    return 0;
}