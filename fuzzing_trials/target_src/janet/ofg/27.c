#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0; // Not enough data to form a Janet object
    }

    // Initialize Janet runtime
    janet_init();

    // Create a Janet object from the input data
    Janet janet_obj;
    memcpy(&janet_obj, data, sizeof(Janet));

    // Ensure the Janet object is valid
    if (!janet_checktype(janet_obj, JANET_STRING) && 
        !janet_checktype(janet_obj, JANET_SYMBOL) &&
        !janet_checktype(janet_obj, JANET_KEYWORD)) {
        janet_deinit();
        return 0; // Invalid Janet object type for symbol operations
    }

    // Ensure the index is within a reasonable range
    int32_t index = 0; // Default index
    if (size >= sizeof(Janet) + sizeof(int32_t)) {
        memcpy(&index, data + sizeof(Janet), sizeof(int32_t));
    }

    // Call the function-under-test
    JanetSymbol symbol = janet_getsymbol(&janet_obj, index);

    // Cleanup Janet runtime
    janet_deinit();

    return 0;
}