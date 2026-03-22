#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libdwarf.h>
#include <dwarf.h> // Include this header to ensure Dwarf_Unsigned and Dwarf_Signed are defined

int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Ensure there's enough data for all parameters
    }

    // Allocate memory for the parameters
    char *input_data = (char *)malloc(size);
    if (input_data == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(input_data, data, size);

    Dwarf_Unsigned *unsigned_result = (Dwarf_Unsigned *)malloc(sizeof(Dwarf_Unsigned));
    if (unsigned_result == NULL) {
        free(input_data);
        return 0; // Memory allocation failed
    }

    Dwarf_Signed *signed_result = (Dwarf_Signed *)malloc(sizeof(Dwarf_Signed));
    if (signed_result == NULL) {
        free(input_data);
        free(unsigned_result);
        return 0; // Memory allocation failed
    }

    char *end_pointer = input_data + size;

    // Call the function-under-test
    dwarf_decode_signed_leb128(input_data, unsigned_result, signed_result, end_pointer);

    // Free allocated memory
    free(input_data);
    free(unsigned_result);
    free(signed_result);

    return 0;
}