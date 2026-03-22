#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int dwarf_get_ATE_name(unsigned int ate, const char **ate_name);

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int ate = *(unsigned int *)data;

    // Declare a pointer for the ATE name
    const char *ate_name = NULL;

    // Call the function-under-test
    int result = dwarf_get_ATE_name(ate, &ate_name);

    // Optionally, you can do something with the result or ate_name
    // For example, check the result or print the name if debugging

    return 0;
}