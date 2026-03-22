#include <stdint.h>
#include <stdlib.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = (Dwarf_Debug)data;  // Cast data to Dwarf_Debug
    Dwarf_Bool is_info = 1;  // Initialize with a non-zero value
    Dwarf_Gnu_Index_Head index_head = NULL;
    Dwarf_Unsigned index_version = 0;
    Dwarf_Error error = NULL;

    // Call the function-under-test
    int result = dwarf_get_gnu_index_head(dbg, is_info, &index_head, &index_version, &error);

    // Clean up if necessary
    if (index_head) {
        dwarf_dealloc(dbg, index_head, DW_DLA_GNU_INDEX_HEAD);
    }
    if (error) {
        dwarf_dealloc(dbg, error, DW_DLA_ERROR);
    }

    return 0;
}