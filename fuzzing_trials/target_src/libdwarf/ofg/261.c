#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    Dwarf_Die die;
    Dwarf_Die child_die;
    Dwarf_Error error;

    // Ensure the size is sufficient for a Dwarf_Die structure
    if (size < sizeof(Dwarf_Die)) {
        return 0;
    }

    // Copy the data into die
    memcpy(&die, data, sizeof(Dwarf_Die));

    // Call the function-under-test
    int result = dwarf_child(die, &child_die, &error);

    // To avoid unused variable warning
    (void)result;

    return 0;
}