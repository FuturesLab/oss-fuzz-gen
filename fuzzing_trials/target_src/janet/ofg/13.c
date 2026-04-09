#include <stdint.h>
#include <stddef.h>

// Function under test
void janet_gcunlock(int);

// Fuzzing harness
int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    int input_value;

    // Ensure that size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Copy data into input_value ensuring no overflow
    input_value = *(const int *)data;

    // Call the function under test
    janet_gcunlock(input_value);

    return 0;
}