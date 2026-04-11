#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <janet.h>

extern int16_t janet_getinteger16(const Janet *, int32_t);

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    Janet janet_value;
    int32_t index;

    // Initialize the Janet object with a valid type and value
    janet_value = janet_wrap_integer(0); // For example, wrap an integer

    // Copy the index from the input data
    memcpy(&index, data, sizeof(int32_t));

    // Ensure the index is within a reasonable range
    index = index % 100; // Assuming a max index of 100 for demonstration

    // Call the function-under-test
    int16_t result = janet_getinteger16(&janet_value, index);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}