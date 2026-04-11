#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern long long hts_parse_decimal(const char *str, char **endptr, int flags);

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Prepare variables for the function call
    char *endptr = NULL;
    int flags = 0; // You can try different flag values as needed

    // Call the function-under-test
    long long result = hts_parse_decimal(input, &endptr, flags);

    // Free the allocated memory
    free(input);

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}