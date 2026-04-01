#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    // Copy the data into the input buffer and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    sqlite3_compileoption_used(input);

    // Free the allocated memory
    free(input);

    return 0;
}

#ifdef __cplusplus
}
#endif