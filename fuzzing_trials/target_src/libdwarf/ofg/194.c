#include <stdint.h>
#include <stddef.h>

// Assume the function is defined in some library we are linking against
extern int dwarf_get_LNE_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Ensure we have enough data to read an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the data
    unsigned int index = *(unsigned int *)data;

    // Prepare a pointer for the output string
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_LNE_name(index, &name);

    // Optionally, you can perform additional checks or operations on 'name' here

    return 0;
}