#include <stdint.h>
#include <stddef.h> // Include this for size_t

// Assuming the function is declared in some header file
// int dwarf_set_reloc_application(int);

extern int dwarf_set_reloc_application(int);

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first four bytes of data as an integer
    int input_value = *(const int *)data;

    // Call the function-under-test
    dwarf_set_reloc_application(input_value);

    return 0;
}