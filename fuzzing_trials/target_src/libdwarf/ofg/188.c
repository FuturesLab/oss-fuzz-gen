#include <stdint.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int dwarf_get_fde_info_for_reg3_b(Dwarf_Fde, Dwarf_Half, Dwarf_Addr, Dwarf_Small *, Dwarf_Unsigned *, Dwarf_Unsigned *, Dwarf_Unsigned *, Dwarf_Block *, Dwarf_Addr *, Dwarf_Bool *, Dwarf_Addr *, Dwarf_Error *);

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Fde) + sizeof(Dwarf_Half) + sizeof(Dwarf_Addr)) {
        return 0;
    }

    Dwarf_Fde fde = (Dwarf_Fde)data;
    Dwarf_Half reg = *(Dwarf_Half *)(data + sizeof(Dwarf_Fde));
    Dwarf_Addr pc = *(Dwarf_Addr *)(data + sizeof(Dwarf_Fde) + sizeof(Dwarf_Half));

    Dwarf_Small value_type = 0;
    Dwarf_Unsigned offset_relevant = 0;
    Dwarf_Unsigned register_num = 0;
    Dwarf_Unsigned offset_or_block_len = 0;
    Dwarf_Block block = {0};
    Dwarf_Addr row_pc = 0;
    Dwarf_Bool has_more_rows = 0;
    Dwarf_Addr subsequent_pc = 0;
    Dwarf_Error error = NULL;

    int result = dwarf_get_fde_info_for_reg3_b(fde, reg, pc, &value_type, &offset_relevant, &register_num, &offset_or_block_len, &block, &row_pc, &has_more_rows, &subsequent_pc, &error);

    return 0;
}