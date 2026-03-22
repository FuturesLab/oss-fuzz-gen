#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assume the function is declared in a header file
// #include "dwarf.h"

int dwarf_get_MACRO_name(unsigned int index, const char **name);

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0; // Not enough data to form an unsigned int
    }

    // Extract an unsigned int from the input data
    unsigned int index = *(const unsigned int *)data;

    // Prepare a pointer to hold the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_MACRO_name(index, &name);

    // Optionally print the result and name for debugging purposes
    if (name != NULL) {
        printf("Result: %d, Name: %s\n", result, name);
    } else {
        printf("Result: %d, Name: NULL\n", result);
    }

    return 0;
}