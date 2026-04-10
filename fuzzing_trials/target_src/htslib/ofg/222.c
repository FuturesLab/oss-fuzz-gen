#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
uint32_t bam_auxB_len(const uint8_t *data);

int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL and has some size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    uint32_t result = bam_auxB_len(data);

    // Optionally, do something with the result to avoid compiler optimizations
    (void)result;

    return 0;
}