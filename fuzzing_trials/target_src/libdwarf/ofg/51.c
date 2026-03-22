#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    Dwarf_Attribute attr;
    Dwarf_Off offset;
    Dwarf_Error error;
    int result;

    // Initialize Dwarf_Attribute with some non-NULL value
    attr = (Dwarf_Attribute)data;

    // Call the function-under-test
    result = dwarf_global_formref(attr, &offset, &error);

    // Return 0 to indicate the function executed
    return 0;
}