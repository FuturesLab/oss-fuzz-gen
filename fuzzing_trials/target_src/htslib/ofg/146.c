#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test declaration
char * bam_aux2Z(const uint8_t *data);

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test
    char *result = bam_aux2Z(data);

    // If the function returns a non-NULL pointer, free it
    if (result != NULL) {
        free(result);
    }

    return 0;
}