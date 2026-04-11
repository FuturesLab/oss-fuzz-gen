#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
long long hts_parse_decimal(const char *str, char **endptr, int flags);

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid C-string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string and ensure it's null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (!input_str) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Initialize the endptr and flags
    char *endptr = NULL;
    int flags = 0; // You can experiment with different flag values

    // Call the function-under-test
    long long result = hts_parse_decimal(input_str, &endptr, flags);

    // Free allocated memory
    free(input_str);

    return 0;
}