#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <janet.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Ensure there is enough data to work with
    if (size < sizeof(int32_t)) {
        janet_deinit();
        return 0;
    }

    // Create a JanetArray
    JanetArray *array = janet_array(10);

    // Extract an int32_t value from the data
    int32_t count;
    memcpy(&count, data, sizeof(int32_t));

    // Call the function-under-test
    janet_array_setcount(array, count);

    // Clean up
    janet_deinit();
    return 0;
}