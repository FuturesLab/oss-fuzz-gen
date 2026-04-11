#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Define a dummy JanetCFunction for testing purposes
static Janet cfunction_dummy(int32_t argc, Janet *argv) {
    (void)argc; // Unused parameter
    (void)argv; // Unused parameter
    return janet_wrap_nil();
}

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to extract necessary parameters
    if (size < sizeof(Janet) * 2 + sizeof(int32_t) * 2) {
        return 0;
    }

    // Extract parameters from the input data
    const Janet *janet_array = (const Janet *)data;
    int32_t n = *((int32_t *)(data + sizeof(Janet) * 2));
    int32_t def = *((int32_t *)(data + sizeof(Janet) * 2 + sizeof(int32_t)));

    // Ensure n is within a reasonable range to avoid out-of-bounds access
    if (n < 0 || n > size / sizeof(Janet)) {
        return 0;
    }

    // Call the function-under-test
    janet_optcfunction(janet_array, n, def, cfunction_dummy);

    return 0;
}