#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Ensure the size is sufficient to create at least one Janet element
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet array from the input data
    Janet *janet_array = (Janet *)data;
    size_t janet_count = size / sizeof(Janet);

    // Ensure at least one element is present
    if (janet_count == 0) {
        janet_deinit();
        return 0;
    }

    // Use a fixed index for simplicity, within bounds
    int32_t index = 0;

    // Call the function-under-test
    JanetView result = janet_getindexed(janet_array, index);

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}