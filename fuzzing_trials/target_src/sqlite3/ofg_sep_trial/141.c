#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this header for malloc and free

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Create a buffer to hold the null-terminated string
    char *option = (char *)malloc(size + 1);
    if (option == NULL) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(option, data, size);
    option[size] = '\0';

    // Call the function-under-test
    int result = sqlite3_compileoption_used(option);

    // Free the allocated memory
    free(option);

    return 0;
}