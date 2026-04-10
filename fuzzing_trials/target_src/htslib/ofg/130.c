#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h> // Include this for PRId64

// Assuming hts_pos_t is defined as a 64-bit integer
typedef int64_t hts_pos_t;

// Function signature for the function-under-test
const char * hts_parse_reg64(const char *, hts_pos_t *, hts_pos_t *);

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Initialize start and end positions
    hts_pos_t start = 0;
    hts_pos_t end = 0;

    // Call the function-under-test
    const char *result = hts_parse_reg64(input, &start, &end);

    // Output the result for debugging purposes (optional)
    if (result != NULL) {
        printf("Result: %s, Start: %" PRId64 ", End: %" PRId64 "\n", result, start, end);
    }

    // Free allocated memory
    free(input);

    return 0;
}