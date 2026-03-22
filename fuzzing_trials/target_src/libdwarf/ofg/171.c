#include <stdint.h>
#include <stddef.h>
#include <dwarf.h>

extern int dwarf_get_ATE_name(unsigned int ate, const char **name);

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int ate = *((unsigned int*)data);
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_ATE_name(ate, &name);

    // Use the result and name for further processing or assertions if needed
    // For now, we'll just check if name is not NULL
    if (name != NULL) {
        // Do something with the name if needed
    }

    return 0;
}