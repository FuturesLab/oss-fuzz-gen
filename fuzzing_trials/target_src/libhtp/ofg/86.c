#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
void bstr_util_mem_trim(unsigned char **data, size_t *length);

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid undefined behavior
    if (size == 0) return 0;

    // Allocate memory for the input data
    unsigned char *input_data = (unsigned char *)malloc(size);
    if (input_data == NULL) return 0;

    // Copy the fuzzing data into the allocated memory
    memcpy(input_data, data, size);

    // Initialize the length variable
    size_t length = size;

    // Call the function-under-test
    bstr_util_mem_trim(&input_data, &length);

    // Free the allocated memory
    free(input_data);

    return 0;
}