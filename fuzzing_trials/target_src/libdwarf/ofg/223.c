#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int dwarf_get_EH_name(unsigned int, const char **);

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int eh_code;
    const char *eh_name = NULL;

    // Extract an unsigned int from the input data
    eh_code = *(unsigned int *)data;

    // Call the function-under-test
    int result = dwarf_get_EH_name(eh_code, &eh_name);

    // Ensure eh_name is not NULL before trying to use it
    if (result == DW_DLV_OK && eh_name != NULL) {
        // Optionally, you can do something with eh_name here
    }

    return 0;
}