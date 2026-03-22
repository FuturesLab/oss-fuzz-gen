#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assume the function is declared in a header file
int dwarf_get_ISA_name(unsigned int isa, const char **name);

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0; // Not enough data to extract an unsigned int
    }

    unsigned int isa = *(unsigned int *)data;
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_ISA_name(isa, &name);

    // Optionally, you can print the result and name for debugging purposes
    if (result == 0 && name != NULL) {
        printf("ISA: %u, Name: %s\n", isa, name);
    }

    return 0;
}