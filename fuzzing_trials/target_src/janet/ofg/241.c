#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

// Removed extern "C" since this is C code, not C++
int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Initialize a Janet variable from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Extract the index from the input data
    int32_t index;
    memcpy(&index, data + sizeof(Janet), sizeof(int32_t));

    // Ensure the Janet value is valid
    if (!janet_checktype(janet_value, JANET_POINTER)) {
        return 0;
    }

    // Call the function under test
    void *result = janet_getpointer(&janet_value, index);

    // Use the result to prevent any compiler optimizations that might skip the function call
    if (result != NULL) {
        // Do something with the result, e.g., a dummy operation
        *((volatile void **) &result) = result;
    }

    return 0;
}