#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Attribute)) {
        return 0;
    }

    Dwarf_Attribute attr = (Dwarf_Attribute)data;
    Dwarf_Off offset = 0;
    Dwarf_Bool is_info = 0;
    Dwarf_Error error = 0;

    // Call the function-under-test
    int result = dwarf_global_formref_b(attr, &offset, &is_info, &error);

    (void)result; // To avoid compiler warnings about unused variable

    return 0;
}