#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "libdwarf.h"

extern int dwarf_dnames_sizes(Dwarf_Dnames_Head head, 
                              Dwarf_Unsigned *dn_size, 
                              Dwarf_Unsigned *dn_cu_list_offset, 
                              Dwarf_Unsigned *dn_local_type_unit_count, 
                              Dwarf_Unsigned *dn_local_type_unit_offset, 
                              Dwarf_Unsigned *dn_local_type_unit_size, 
                              Dwarf_Unsigned *dn_local_cu_count, 
                              Dwarf_Unsigned *dn_local_cu_offset, 
                              Dwarf_Unsigned *dn_local_cu_size, 
                              char **dn_section_name, 
                              Dwarf_Unsigned *dn_section_name_len, 
                              Dwarf_Half *dn_version, 
                              Dwarf_Half *dn_offset_size, 
                              Dwarf_Error *error);

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Dnames_Head)) {
        return 0;
    }

    Dwarf_Dnames_Head head = (Dwarf_Dnames_Head)data;
    Dwarf_Unsigned dn_size = 0;
    Dwarf_Unsigned dn_cu_list_offset = 0;
    Dwarf_Unsigned dn_local_type_unit_count = 0;
    Dwarf_Unsigned dn_local_type_unit_offset = 0;
    Dwarf_Unsigned dn_local_type_unit_size = 0;
    Dwarf_Unsigned dn_local_cu_count = 0;
    Dwarf_Unsigned dn_local_cu_offset = 0;
    Dwarf_Unsigned dn_local_cu_size = 0;
    char *dn_section_name = NULL;
    Dwarf_Unsigned dn_section_name_len = 0;
    Dwarf_Half dn_version = 0;
    Dwarf_Half dn_offset_size = 0;
    Dwarf_Error error = NULL;

    dwarf_dnames_sizes(head, 
                       &dn_size, 
                       &dn_cu_list_offset, 
                       &dn_local_type_unit_count, 
                       &dn_local_type_unit_offset, 
                       &dn_local_type_unit_size, 
                       &dn_local_cu_count, 
                       &dn_local_cu_offset, 
                       &dn_local_cu_size, 
                       &dn_section_name, 
                       &dn_section_name_len, 
                       &dn_version, 
                       &dn_offset_size, 
                       &error);

    return 0;
}