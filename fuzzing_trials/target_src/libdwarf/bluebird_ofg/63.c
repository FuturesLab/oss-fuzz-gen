#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include "libdwarf.h"

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = 0; // Assuming a valid Dwarf_Debug object is initialized elsewhere
    Dwarf_Small *small_data = NULL;
    Dwarf_Unsigned small_size = 0;
    Dwarf_Dsc_Head *dsc_head = NULL;
    Dwarf_Unsigned *ret_count = (Dwarf_Unsigned *)malloc(sizeof(Dwarf_Unsigned));
    Dwarf_Error *error = NULL;

    if (size > 0) {
        small_data = (Dwarf_Small *)malloc(size);
        if (small_data != NULL) {
            memcpy(small_data, data, size);
            small_size = (Dwarf_Unsigned)size;
        }
    }

    // Call the function-under-test
    int result = dwarf_discr_list(dbg, small_data, small_size, dsc_head, ret_count, error);

    // Clean up
    if (small_data != NULL) {
        free(small_data);
    }
    if (ret_count != NULL) {
        free(ret_count);
    }

    return 0;
}