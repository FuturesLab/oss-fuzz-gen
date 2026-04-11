#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a Janet array
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet runtime
    janet_init();

    // Create a Janet array from the input data
    Janet *janetArray = (Janet *)data;

    // Use a fixed index within the bounds of the data size
    int32_t index = 0;
    if (size >= sizeof(Janet) * 2) {
        index = 1; // Use the second element if possible
    }

    // Call the function-under-test with the Janet array and index
    JanetTable *result = janet_gettable(janetArray, index);

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}