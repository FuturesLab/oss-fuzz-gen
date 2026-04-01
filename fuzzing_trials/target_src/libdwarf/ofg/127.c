#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <libdwarf.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input_value;
    memcpy(&input_value, data, sizeof(int));

    // Call the function-under-test
    Dwarf_Bool result = dwarf_addr_form_is_indexed(input_value);

    // Use the result to prevent compiler optimizations from removing the call
    if (result) {
        // Do something with the result if needed
    }

    return 0;
}