#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Dnames_Head) + 5 * sizeof(Dwarf_Unsigned) + 2 * sizeof(Dwarf_Half)) {
        return 0;
    }

    // Initialize variables
    Dwarf_Dnames_Head dnames_head = (Dwarf_Dnames_Head)data;
    Dwarf_Unsigned offset = *(Dwarf_Unsigned *)(data + sizeof(Dwarf_Dnames_Head));
    Dwarf_Unsigned abbrev_offset, abbrev_count, abbrev_entry_size;
    Dwarf_Unsigned entry_offset = *(Dwarf_Unsigned *)(data + sizeof(Dwarf_Dnames_Head) + sizeof(Dwarf_Unsigned));
    Dwarf_Half form, attr;

    // Call the function-under-test
    int result = dwarf_dnames_abbrevtable(
        dnames_head,
        offset,
        &abbrev_offset,
        &abbrev_count,
        &abbrev_entry_size,
        entry_offset,
        &form,
        &attr,
        &abbrev_entry_size
    );

    return 0;
}