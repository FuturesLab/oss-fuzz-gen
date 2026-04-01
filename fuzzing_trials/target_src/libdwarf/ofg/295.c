#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assuming the function is declared in a header file
int dwarf_get_IDX_name(unsigned int index, const char **name);

int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the data
    unsigned int index = *(unsigned int *)data;

    // Declare a pointer for the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_IDX_name(index, &name);

    // Optionally, you can print the result or the name for debugging purposes
    // printf("Result: %d, Name: %s\n", result, name ? name : "NULL");

    return 0;
}