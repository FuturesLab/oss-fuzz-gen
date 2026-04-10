#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern const char * hts_parse_reg(const char *, int *, int *);

int LLVMFuzzerTestOneInput_209(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize the integer pointers
    int begin = 0;
    int end = 0;

    // Call the function-under-test
    const char *result = hts_parse_reg(null_terminated_data, &begin, &end);

    // Use the result to avoid compiler optimizations removing the call
    if (result) {
        // Do something with the result if necessary
    }

    // Free the allocated memory
    free(null_terminated_data);

    return 0;
}