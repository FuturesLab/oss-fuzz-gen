#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

extern int dwarf_whatattr(Dwarf_Attribute attr, Dwarf_Half *return_attr, Dwarf_Error *error);

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    if (size < sizeof(Dwarf_Attribute)) {
        return 0; // Not enough data to form a valid Dwarf_Attribute
    }

    Dwarf_Attribute attr = (Dwarf_Attribute)(uintptr_t)data; // Cast data to a pointer type
    Dwarf_Half return_attr = 0;
    Dwarf_Error error = NULL;

    // Call the function-under-test
    dwarf_whatattr(attr, &return_attr, &error);

    return 0;
}