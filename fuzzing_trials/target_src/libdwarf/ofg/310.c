#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Assuming the function is declared in a header file named "dwarf.h"
#include "dwarf.h"

int LLVMFuzzerTestOneInput_310(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int index = *(unsigned int *)data;

    // Prepare a pointer to hold the CFA name
    const char *cfa_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_CFA_name(index, &cfa_name);

    // Optionally, you can add checks or log the result and cfa_name if needed
    // For example:
    // printf("Result: %d, CFA Name: %s\n", result, cfa_name);

    return 0;
}