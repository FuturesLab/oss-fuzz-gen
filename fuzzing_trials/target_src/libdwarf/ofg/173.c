#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Initialize Dwarf_Debug object
    Dwarf_Debug dbg = 0;
    Dwarf_Error err;
    int res = dwarf_init_path("/dev/null", NULL, 0, DW_GROUPNUMBER_ANY, NULL, NULL, &dbg, &err);
    if (res != DW_DLV_OK) {
        return 0;
    }

    // Ensure size is non-zero to avoid zero-length input
    if (size < sizeof(Dwarf_Half)) {
        dwarf_finish(dbg);
        return 0;
    }

    // Extract a Dwarf_Half value from the input data
    Dwarf_Half table_size = *(Dwarf_Half *)data;

    // Call the function-under-test
    Dwarf_Half result = dwarf_set_frame_rule_table_size(dbg, table_size);

    // Clean up
    dwarf_finish(dbg);

    return 0;
}