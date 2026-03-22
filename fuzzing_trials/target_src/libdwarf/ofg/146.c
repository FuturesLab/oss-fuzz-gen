#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <dwarf.h>

// Function prototype for the function-under-test
int dwarf_get_ATCF_name(unsigned int attr, const char **name);

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int attr = *(const unsigned int *)data;

    // Initialize a pointer for the name
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_ATCF_name(attr, &name);

    // Optionally, you can add some checks or operations on 'result' and 'name'
    // For example, you might want to print the result or name for debugging
    // But remember, do not use any form of output in the final fuzzing harness

    return 0;
}