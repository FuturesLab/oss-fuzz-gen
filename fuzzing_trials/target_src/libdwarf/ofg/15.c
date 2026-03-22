#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    Dwarf_Debug dbg = (Dwarf_Debug)(uintptr_t)data; // Casting data to Dwarf_Debug for testing
    Dwarf_Off offset = 0;
    if (size > sizeof(Dwarf_Off)) {
        offset = *((Dwarf_Off *)data); // Extracting offset from data
    }

    Dwarf_Bool is_info = 1; // Setting is_info to true
    Dwarf_Die die = 0; // Initialize die
    Dwarf_Error error = 0; // Initialize error

    // Call the function-under-test
    int result = dwarf_offdie_b(dbg, offset, is_info, &die, &error);

    // Normally you would do something with the result, die, or error
    // For fuzzing purposes, we just call the function

    return 0;
}

#ifdef __cplusplus
}
#endif