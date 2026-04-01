#include <stddef.h>
#include <stdint.h>
#include <libdwarf.h>
#include <dwarf.h>

int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    if (size < sizeof(Dwarf_Signed) + sizeof(int) + 1) {
        return 0; // Not enough data to properly initialize parameters
    }

    // Initialize parameters for the function-under-test
    Dwarf_Signed signed_value = *(Dwarf_Signed *)data;
    int leb128_length = 0;
    char buffer[256]; // Ensure buffer is large enough for encoded LEB128
    int buffer_size = sizeof(buffer);

    // Call the function-under-test
    dwarf_encode_signed_leb128(signed_value, &leb128_length, buffer, buffer_size);

    return 0;
}