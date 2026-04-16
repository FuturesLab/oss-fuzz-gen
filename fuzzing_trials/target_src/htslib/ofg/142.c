#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assume the function is declared in some header file
int hfile_list_schemes(const char *input, const char **schemes, int *num_schemes);

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for meaningful input
    if (size < 2) {
        return 0;
    }

    // Allocate memory for input string and copy data into it
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';  // Null-terminate the string

    // Prepare the schemes array and num_schemes
    const char *schemes[10];  // Arbitrary size for demonstration
    int num_schemes = 0;

    // Call the function-under-test
    int result = hfile_list_schemes(input, schemes, &num_schemes);

    // Free allocated memory
    free(input);

    return 0;
}