#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
void bstr_util_mem_trim(unsigned char **buffer, size_t *size);

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Allocate memory for the buffer, ensuring it's non-NULL
    unsigned char *buffer = (unsigned char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Initialize the size variable
    size_t buffer_size = size;

    // Call the function-under-test
    bstr_util_mem_trim(&buffer, &buffer_size);

    // Free the allocated memory
    free(buffer);

    return 0;
}