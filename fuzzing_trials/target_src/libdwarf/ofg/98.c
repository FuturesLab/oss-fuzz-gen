#include <stddef.h>
#include <stdint.h>

// Function-under-test declaration
int dwarf_set_stringcheck(int);

// Fuzzing harness
int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input_value = *((int*)data);

    // Call the function-under-test
    dwarf_set_stringcheck(input_value);

    return 0;
}