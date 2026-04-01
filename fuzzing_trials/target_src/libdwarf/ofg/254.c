#include <stdint.h>
#include <stddef.h>
#include <dwarf.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = (Dwarf_Debug)(uintptr_t)data; // Dummy initialization
    int index = size > 0 ? data[0] : 0; // Use the first byte of data as index
    const char *section_name = NULL;
    Dwarf_Addr section_addr = 0;
    Dwarf_Unsigned section_size = 0;
    Dwarf_Error error = NULL;

    // Call the function-under-test
    int result = dwarf_get_section_info_by_index(dbg, index, &section_name, &section_addr, &section_size, &error);

    // Optionally handle the result or error, but for fuzzing, we mainly want to ensure it runs
    (void)result;
    (void)section_name;
    (void)section_addr;
    (void)section_size;
    (void)error;

    return 0;
}