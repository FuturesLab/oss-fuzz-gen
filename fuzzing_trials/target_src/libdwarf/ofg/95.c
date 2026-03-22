#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Initialize variables
    Dwarf_Global global;
    Dwarf_Off offset;
    Dwarf_Error error;

    // Ensure the data size is sufficient for the test
    if (size < sizeof(Dwarf_Global)) {
        return 0;
    }

    // Cast the input data to Dwarf_Global
    global = (Dwarf_Global)data;

    // Call the function-under-test
    int result = dwarf_global_die_offset(global, &offset, &error);

    // Use the result, offset, and error as needed (for debugging, logging, etc.)
    // For this fuzzing harness, we just return the result.
    return result;
}