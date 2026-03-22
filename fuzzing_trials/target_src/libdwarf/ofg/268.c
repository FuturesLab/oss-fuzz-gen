#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int dwarf_dnames_entrypool_values(Dwarf_Dnames_Head dnames_head, 
                                         Dwarf_Unsigned index, 
                                         Dwarf_Unsigned offset, 
                                         Dwarf_Unsigned entry_length, 
                                         Dwarf_Half *attr, 
                                         Dwarf_Half *form, 
                                         Dwarf_Unsigned *value, 
                                         Dwarf_Sig8 *sig8, 
                                         Dwarf_Bool *is_single, 
                                         Dwarf_Unsigned *entry_off, 
                                         Dwarf_Unsigned *entry_len, 
                                         Dwarf_Error *error);

int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Unsigned) * 3) {
        return 0;
    }

    Dwarf_Dnames_Head dnames_head = (Dwarf_Dnames_Head)data;
    Dwarf_Unsigned index = (Dwarf_Unsigned)data[0];
    Dwarf_Unsigned offset = (Dwarf_Unsigned)data[1];
    Dwarf_Unsigned entry_length = (Dwarf_Unsigned)data[2];
    
    Dwarf_Half attr = 0;
    Dwarf_Half form = 0;
    Dwarf_Unsigned value = 0;
    Dwarf_Sig8 sig8;
    Dwarf_Bool is_single = 0;
    Dwarf_Unsigned entry_off = 0;
    Dwarf_Unsigned entry_len = 0;
    Dwarf_Error error = NULL;

    int result = dwarf_dnames_entrypool_values(dnames_head, index, offset, entry_length, 
                                               &attr, &form, &value, &sig8, &is_single, 
                                               &entry_off, &entry_len, &error);

    return 0;
}