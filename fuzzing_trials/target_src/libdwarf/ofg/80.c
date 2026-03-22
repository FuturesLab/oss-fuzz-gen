#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assuming the function is declared in a header file
int dwarf_get_SECT_name(unsigned int sect_no, const char **name);

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0; // Not enough data to extract an unsigned int
    }

    unsigned int sect_no;
    const char *sect_name = NULL;

    // Extract an unsigned int from the input data
    sect_no = *(unsigned int *)data;

    // Call the function-under-test
    int result = dwarf_get_SECT_name(sect_no, &sect_name);

    // Optionally, you can print the result or the section name for debugging
    if (sect_name != NULL) {
        printf("Section Name: %s\n", sect_name);
    }

    return 0;
}