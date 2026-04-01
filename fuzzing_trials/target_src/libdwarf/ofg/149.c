#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dwarf.h>

extern int dwarf_get_LNS_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    unsigned int lns_index;
    const char *lns_name;

    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    lns_index = *((unsigned int *)data);

    // Call the function-under-test
    int result = dwarf_get_LNS_name(lns_index, &lns_name);

    // Optionally, you can print the result and the name for debugging purposes
    // printf("Result: %d, LNS Name: %s\n", result, lns_name);

    return 0;
}