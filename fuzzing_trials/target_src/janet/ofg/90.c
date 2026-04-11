#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a Janet object
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj = janet_wrap_integer((int32_t)data[0]);

    // Call the function-under-test
    int result = janet_gcunroot(janet_obj);

    // Use the result in some way to prevent compiler optimizations
    (void)result;

    return 0;
}