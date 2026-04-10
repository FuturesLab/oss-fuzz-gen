#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Ensure we have at least one Janet object and an int32_t index
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Extract the Janet object and the int32_t index from the data
    const Janet *janet_array = (const Janet *)data;
    int32_t index = *((const int32_t *)(data + sizeof(Janet)));

    // Ensure the index is within bounds
    if (index < 0 || index >= size / sizeof(Janet)) {
        return 0;
    }

    // Call the function-under-test
    uint32_t result = janet_getuinteger(janet_array, index);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}