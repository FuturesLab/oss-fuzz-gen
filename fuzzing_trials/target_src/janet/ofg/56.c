#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Initialize a Janet object
    Janet janet_value;

    // Check if the size is at least the size of an int64_t
    if (size >= sizeof(int64_t)) {
        // Cast the data to an int64_t pointer and dereference it
        int64_t value = *(int64_t *)data;

        // Create a Janet integer from the int64_t value
        janet_value = janet_wrap_integer(value);

        // Call the function-under-test
        int64_t result = janet_unwrap_s64(janet_value);

        // Use the result in some way to prevent compiler optimizations from removing the call
        (void)result;
    }

    return 0;
}