#include <stdint.h>
#include <stddef.h>

// Function-under-test
int dwarf_set_stringcheck(int);

// Fuzzing harness
int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int check_value = 0;
    for (size_t i = 0; i < sizeof(int); i++) {
        check_value |= (data[i] << (i * 8));
    }

    // Call the function-under-test with the extracted integer
    dwarf_set_stringcheck(check_value);

    return 0;
}