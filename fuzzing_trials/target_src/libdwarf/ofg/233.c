#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Include the necessary header for the function prototype
extern int dwarf_get_END_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the data
    unsigned int input_value = *(unsigned int *)data;

    // Prepare a non-NULL pointer for the second parameter
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_END_name(input_value, &name);

    // Optionally, you can use the result or name for further checks
    // For now, we just return 0 to indicate the fuzzer can continue
    return 0;
}