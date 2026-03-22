#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>
#include <dwarf.h> // Include this for Dwarf_Attribute, Dwarf_Unsigned, Dwarf_Error

extern int dwarf_get_debug_str_index(Dwarf_Attribute attr, Dwarf_Unsigned *index, Dwarf_Error *error);

int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Attribute)) {
        return 0;
    }

    // Initialize variables
    Dwarf_Attribute attr = *(Dwarf_Attribute *)data;
    Dwarf_Unsigned index = 0;
    Dwarf_Error error = NULL;

    // Call the function-under-test
    dwarf_get_debug_str_index(attr, &index, &error);

    return 0;
}