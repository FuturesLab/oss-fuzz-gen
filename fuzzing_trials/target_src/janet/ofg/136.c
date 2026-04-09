#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

// Fuzzing harness for janet_getfunction
int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a Janet value and an int32_t index
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Extract a Janet value from the data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Extract an int32_t index from the data
    int32_t index;
    memcpy(&index, data + sizeof(Janet), sizeof(int32_t));

    // Ensure the Janet value is a valid type for janet_getfunction
    if (!janet_checktype(janet_value, JANET_FUNCTION)) {
        return 0;
    }

    // Call the function-under-test
    JanetFunction *result = janet_getfunction(&janet_value, index);

    // Use the result to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Perform some trivial operation with the result
        (void)result->def;
    }

    return 0;
}