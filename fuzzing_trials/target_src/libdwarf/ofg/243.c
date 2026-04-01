#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_243(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = 0; // Initialize Dwarf_Debug to a valid value
    Dwarf_Half value;

    if (size < sizeof(Dwarf_Half)) {
        return 0; // Ensure there is enough data to read a Dwarf_Half value
    }

    // Initialize Dwarf_Half with data from the input
    value = *((Dwarf_Half *)data);

    // Call the function-under-test
    dwarf_set_frame_rule_initial_value(dbg, value);

    return 0;
}