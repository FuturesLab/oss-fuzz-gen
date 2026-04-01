#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
char * bstr_util_memdup_to_c(const void *src, size_t size);

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    char *result = bstr_util_memdup_to_c((const void *)data, size);

    // Free the result if it's not NULL to avoid memory leaks
    if (result != NULL) {
        free(result);
    }

    return 0;
}