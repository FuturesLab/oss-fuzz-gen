#include <stdint.h>
#include <stddef.h>

// Assuming the function is declared somewhere
int dwarf_set_de_alloc_flag(int flag);

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Interpret the first 4 bytes of data as an int
    int flag = *(const int *)data;

    // Call the function-under-test
    dwarf_set_de_alloc_flag(flag);

    return 0;
}