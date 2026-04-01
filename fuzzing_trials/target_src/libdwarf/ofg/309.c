#include <stdint.h>
#include <stddef.h>

// Assume the function is declared in some header file
int dwarf_get_CFA_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int index = *((unsigned int *)data);
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_CFA_name(index, &name);

    // Optionally, you can add some checks or logging here
    // For example, checking if name is not NULL and result is as expected

    return 0;
}