#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_350(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t) * 2 + sizeof(uint8_t)) {
        return 0;
    }

    // Initialize the parameters
    const Janet *janet_ptr = (const Janet *)data;
    int32_t index = *(const int32_t *)(data + sizeof(Janet));
    int32_t def = *(const int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    const uint8_t *sym = data + sizeof(Janet) + sizeof(int32_t) * 2;

    // Ensure sym is null-terminated for safety
    size_t sym_length = size - (sizeof(Janet) + sizeof(int32_t) * 2);
    uint8_t *sym_buffer = (uint8_t *)malloc(sym_length + 1);
    if (!sym_buffer) {
        return 0;
    }
    memcpy(sym_buffer, sym, sym_length);
    sym_buffer[sym_length] = '\0';

    // Validate the Janet pointer before using it
    if (!janet_checktype(*janet_ptr, JANET_NIL) &&
        !janet_checktype(*janet_ptr, JANET_STRING) &&
        !janet_checktype(*janet_ptr, JANET_SYMBOL) &&
        !janet_checktype(*janet_ptr, JANET_KEYWORD)) {
        free(sym_buffer);
        return 0;
    }

    // Call the function-under-test
    JanetSymbol result = janet_optsymbol(janet_ptr, index, def, (const char *)sym_buffer);

    // Clean up
    free(sym_buffer);

    return 0;
}