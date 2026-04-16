#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Function-under-test declaration
char * bam_aux2Z(const uint8_t *data);

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has a minimum size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    char *result = bam_aux2Z(data);

    // If the result is not NULL, free the allocated memory
    if (result != NULL) {
        free(result);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif