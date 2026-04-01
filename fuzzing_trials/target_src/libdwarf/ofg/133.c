#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int dwarf_get_MACINFO_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int macinfo_code;
    const char *name = NULL;

    // Extract an unsigned int from the input data
    macinfo_code = *(unsigned int *)data;

    // Call the function-under-test
    int result = dwarf_get_MACINFO_name(macinfo_code, &name);

    // Optionally, check the result and the name (if not NULL)
    if (result == DW_DLV_OK && name != NULL) {
        // Do something with the name if needed
    }

    return 0;
}