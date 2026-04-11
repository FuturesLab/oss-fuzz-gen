#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
void janet_gcunlock(int);

// Fuzzing harness
int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Interpret the first bytes of data as an integer
    int input_value = *((int *)data);

    // Call the function-under-test
    janet_gcunlock(input_value);

    return 0;
}