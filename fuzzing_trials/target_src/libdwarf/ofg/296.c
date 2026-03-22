#include <stddef.h>
#include <stdint.h>
#include <libdwarf.h>

extern int dwarf_get_IDX_name(unsigned int index, const char **name);

int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    unsigned int index;
    const char *name = NULL;

    // Ensure we have enough data to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    index = *((unsigned int *)data);

    // Call the function-under-test
    int result = dwarf_get_IDX_name(index, &name);

    // Optionally, you can add checks or log the result and name
    // For example:
    // printf("Result: %d, Name: %s\n", result, name ? name : "NULL");

    return 0;
}