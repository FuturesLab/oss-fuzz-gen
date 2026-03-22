#include <stdint.h>
#include <stddef.h>

// Assuming the function is defined in an external library
extern int dwarf_set_de_alloc_flag(int flag);

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte of data to use
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data as the flag parameter
    int flag = (int)data[0];

    // Call the function-under-test
    dwarf_set_de_alloc_flag(flag);

    return 0;
}