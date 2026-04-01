#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <libdwarf.h> // Include the necessary header for the function

extern int dwarf_decode_signed_leb128(char *leb128, Dwarf_Unsigned *length, Dwarf_Signed *value, char *endptr);

int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there is at least some data to process

    // Allocate memory for the leb128 input
    char *leb128 = (char *)malloc(size);
    if (leb128 == NULL) return 0;
    
    // Copy the input data to the leb128 buffer
    for (size_t i = 0; i < size; i++) {
        leb128[i] = (char)data[i];
    }

    // Initialize the output variables
    Dwarf_Unsigned length = 0;
    Dwarf_Signed value = 0;
    char *endptr = NULL;

    // Call the function-under-test
    dwarf_decode_signed_leb128(leb128, &length, &value, endptr);

    // Free the allocated memory
    free(leb128);

    return 0;
}