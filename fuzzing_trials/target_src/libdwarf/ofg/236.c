#include <stdint.h>
#include <stddef.h>
#include <dwarf.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    Dwarf_Global global;
    Dwarf_Off offset = 0;
    Dwarf_Error error = NULL;

    // Ensure that the data size is sufficient for the test
    if (size < sizeof(Dwarf_Global)) {
        return 0;
    }

    // Cast the data to a pointer to Dwarf_Global type
    global = (Dwarf_Global)data;

    // Call the function-under-test
    int result = dwarf_global_cu_offset(global, &offset, &error);

    // Handle the result if needed (e.g., check for errors)
    if (result != DW_DLV_OK) {
        // Handle error if necessary
    }

    return 0;
}