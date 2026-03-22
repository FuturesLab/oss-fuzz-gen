#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libdwarf.h"

extern int dwarf_dnames_name(Dwarf_Dnames_Head, Dwarf_Unsigned, Dwarf_Unsigned *, Dwarf_Unsigned *, Dwarf_Unsigned *, char **, Dwarf_Unsigned *, Dwarf_Unsigned *, Dwarf_Half *, Dwarf_Unsigned, Dwarf_Half *, Dwarf_Half *, Dwarf_Unsigned *, Dwarf_Error *);

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Unsigned)) {
        return 0;
    }

    Dwarf_Dnames_Head head = (Dwarf_Dnames_Head)(uintptr_t)data;
    Dwarf_Unsigned index = *(Dwarf_Unsigned *)data;
    Dwarf_Unsigned name_index = 0;
    Dwarf_Unsigned offset = 0;
    Dwarf_Unsigned cu_index = 0;
    char *name = NULL;
    Dwarf_Unsigned name_len = 0;
    Dwarf_Unsigned form = 0;
    Dwarf_Half attr = 0;
    Dwarf_Unsigned die_offset = 0;
    Dwarf_Half tag = 0;
    Dwarf_Half form_class = 0;
    Dwarf_Unsigned cu_offset = 0;
    Dwarf_Error error = NULL;

    int result = dwarf_dnames_name(head, index, &name_index, &offset, &cu_index, &name, &name_len, &form, &attr, die_offset, &tag, &form_class, &cu_offset, &error);

    if (name) {
        free(name);
    }

    return 0;
}