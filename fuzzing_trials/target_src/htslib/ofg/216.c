#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
char bam_aux2A(const uint8_t *data);

// Fuzzing harness
int LLVMFuzzerTestOneInput_216(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and size is greater than zero
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    char result = bam_aux2A(data);

    // Use the result in some way to prevent the compiler from optimizing it away
    if (result != '\0') {
        // Do something with the result if needed
    }

    return 0;
}