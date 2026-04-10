#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
char bam_aux2A(const uint8_t *data);

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL and has at least one byte
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    char result = bam_aux2A(data);

    // Use the result in some way to avoid compiler optimizations
    // that might remove the call to bam_aux2A
    (void)result;

    return 0;
}