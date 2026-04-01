#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <libdwarf.h>

extern int dwarf_discr_list(Dwarf_Debug dbg, Dwarf_Small *bytes, Dwarf_Unsigned length, Dwarf_Dsc_Head *dsc_head, Dwarf_Unsigned *dsc_count, Dwarf_Error *error);

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = 0; // Assuming a valid Dwarf_Debug object is initialized elsewhere
    Dwarf_Small *bytes;
    Dwarf_Unsigned length;
    Dwarf_Dsc_Head dsc_head;
    Dwarf_Unsigned dsc_count;
    Dwarf_Error error;

    // Ensure size is non-zero for meaningful input
    if (size == 0) {
        return 0;
    }

    // Allocate memory for bytes and copy data
    bytes = (Dwarf_Small *)malloc(size);
    if (!bytes) {
        return 0;
    }
    memcpy(bytes, data, size);
    length = (Dwarf_Unsigned)size;

    // Initialize dsc_head and dsc_count
    dsc_head = NULL;
    dsc_count = 0;

    // Call the function-under-test
    int result = dwarf_discr_list(dbg, bytes, length, &dsc_head, &dsc_count, &error);

    // Free allocated memory
    free(bytes);

    return 0;
}