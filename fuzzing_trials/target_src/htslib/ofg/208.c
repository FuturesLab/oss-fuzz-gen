#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern const char *hts_parse_reg(const char *, int *, int *);

int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the input string and ensure it is null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Initialize start and end integers
    int start = 0;
    int end = 0;

    // Call the function-under-test
    const char *result = hts_parse_reg(input_str, &start, &end);

    // Free allocated memory
    free(input_str);

    return 0;
}