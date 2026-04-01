#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "dwarf.h"

// Function prototype for the function-under-test
int dwarf_get_LNS_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int lns_index = *(unsigned int *)data;

    // Declare a pointer for the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_LNS_name(lns_index, &name);

    // Optionally, print the result and name for debugging purposes
    if (result == 0 && name != NULL) {
        printf("LNS Name: %s\n", name);
    }

    return 0;
}