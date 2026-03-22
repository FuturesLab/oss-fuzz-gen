#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Assume the function is declared in some header file
int dwarf_get_ORD_name(unsigned int ord, const char **name);

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int ord = *(unsigned int *)data;

    // Initialize a pointer for the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_ORD_name(ord, &name);

    // Optionally, print the result and name for debugging
    if (result == 0 && name != NULL) {
        printf("ORD: %u, Name: %s\n", ord, name);
    }

    return 0;
}