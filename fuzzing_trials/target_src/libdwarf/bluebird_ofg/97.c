#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <stdlib.h>  // Include for malloc
#include "libdwarf.h"

// Forward declare the struct since it is incomplete in the header
struct Dwarf_Global_s;

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // We cannot determine the exact size of Dwarf_Global_s due to its incomplete type,
    // so we will assume a reasonable size for fuzzing purposes.
    size_t assumed_size = 128; // Assumed size for fuzzing

    if (size < assumed_size) {
        return 0;
    }

    // Dynamically allocate memory for a Dwarf_Global structure
    struct Dwarf_Global_s *global = (struct Dwarf_Global_s *)malloc(assumed_size);
    if (!global) {
        return 0; // Allocation failed
    }

    Dwarf_Global dwarf_global = global;

    // Copy the data into the Dwarf_Global structure
    memcpy(global, data, assumed_size);

    // Call the function-under-test
    Dwarf_Half tag_number = dwarf_global_tag_number(dwarf_global);

    // Use the tag_number in some way to avoid compiler optimizations
    (void)tag_number;

    // Free the allocated memory
    free(global);

    return 0;
}