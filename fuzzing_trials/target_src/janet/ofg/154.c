#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Fuzzing harness for janet_gettable
int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to contain at least one Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    // Cast the input data to a Janet object
    const Janet *janet_data = (const Janet *)data;

    // Use a fixed index for fuzzing as the data size might not be large enough for variable indices
    int32_t index = 0;

    // Call the function-under-test
    JanetTable *result = janet_gettable(janet_data, index);

    // Perform cleanup
    janet_deinit();

    return 0;
}