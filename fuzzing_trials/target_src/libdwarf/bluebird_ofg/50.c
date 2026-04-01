#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "libdwarf.h"

extern int dwarf_get_INL_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int index = *(unsigned int *)data;
    const char *name = NULL;

    // Call the function-under-test
    int result = dwarf_get_INL_name(index, &name);

    // Optionally, you can check the result or use the name, but it's not necessary for fuzzing
    if (result == DW_DLV_OK && name != NULL) {
        // Do something with name if needed
    }

    return 0;
}