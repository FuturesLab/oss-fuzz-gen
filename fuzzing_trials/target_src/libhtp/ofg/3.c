#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
char * bstr_util_memdup_to_c(const void *src, size_t size);

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Ensure size is greater than 0 to avoid calling with NULL pointer
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    char *result = bstr_util_memdup_to_c(data, size);

    // Free the result if it's not NULL
    if (result != NULL) {
        free(result);
    }

    return 0;
}