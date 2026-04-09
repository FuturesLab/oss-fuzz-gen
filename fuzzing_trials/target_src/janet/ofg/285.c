#include <stdint.h>
#include <janet.h>

extern int janet_equals(Janet x, Janet y);

int LLVMFuzzerTestOneInput_285(const uint8_t *data, size_t size) {
    if (size < 2 * sizeof(Janet)) {
        return 0;
    }

    // Ensure we have enough data to create two Janet objects
    Janet x = *(const Janet *)(data);
    Janet y = *(const Janet *)(data + sizeof(Janet));

    // Call the function-under-test
    int result = janet_equals(x, y);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}