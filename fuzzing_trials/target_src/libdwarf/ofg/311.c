#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = (Dwarf_Debug)(uintptr_t)data; // Cast data to Dwarf_Debug
    Dwarf_Small address_size;

    if (size > 0) {
        // Use the first byte of data as the address size
        address_size = (Dwarf_Small)data[0];
    } else {
        // Default address size if size is 0
        address_size = 4;
    }

    // Call the function-under-test
    dwarf_set_default_address_size(dbg, address_size);

    return 0;
}