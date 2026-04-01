#include <stdint.h>
#include <stddef.h>
#include <libdwarf.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Unsigned)) {
        return 0;
    }

    Dwarf_Unsigned errnum;
    // Copy the data into errnum ensuring it does not exceed the size of Dwarf_Unsigned
    errnum = *(const Dwarf_Unsigned *)data;

    // Call the function-under-test
    char *errmsg = dwarf_errmsg_by_number(errnum);

    // Optionally print the error message for debugging purposes
    if (errmsg != NULL) {
        printf("Error message: %s\n", errmsg);
    }

    return 0;
}