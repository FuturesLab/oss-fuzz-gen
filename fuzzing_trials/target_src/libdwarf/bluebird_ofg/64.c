#include <stdint.h>
#include <stddef.h>
#include "libdwarf.h"
#include "dwarf.h"

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input_value = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        input_value |= data[i] << (i * 8);
    }

    // Call the function-under-test
    Dwarf_Bool result = dwarf_addr_form_is_indexed(input_value);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Do something if result is true
        // This block is intentionally left empty
    }

    return 0;
}