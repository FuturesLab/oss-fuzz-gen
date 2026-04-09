#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

// Function signature to fuzz
int32_t janet_getstartrange(const Janet *array, int32_t len, int32_t offset, int32_t def);

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < sizeof(Janet) + 3 * sizeof(int32_t)) {
        return 0;
    }

    // Extract parameters from data
    const Janet *array = (const Janet *)data;
    int32_t len = (int32_t)(*(data + sizeof(Janet)));
    int32_t offset = (int32_t)(*(data + sizeof(Janet) + sizeof(int32_t)));
    int32_t def = (int32_t)(*(data + sizeof(Janet) + 2 * sizeof(int32_t)));

    // Call the function-under-test
    int32_t result = janet_getstartrange(array, len, offset, def);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}