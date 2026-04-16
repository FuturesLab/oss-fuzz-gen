#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h> // Include string.h for memcpy

extern uint32_t janet_optuinteger(const Janet *argv, int32_t n, int32_t def, uint32_t max);

int LLVMFuzzerTestOneInput_282(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t) + sizeof(int32_t) + sizeof(uint32_t)) {
        return 0; // Not enough data to initialize parameters
    }

    // Initialize the parameters safely
    Janet argv[1];
    memcpy(argv, data, sizeof(Janet)); // Copy data into Janet structure

    // Ensure that the integer values are within reasonable ranges
    int32_t n = *(int32_t *)(data + sizeof(Janet));
    int32_t def = *(int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    uint32_t max = *(uint32_t *)(data + sizeof(Janet) + 2 * sizeof(int32_t));

    // Adjust n to be within a valid range for the argv array
    n = n % 1; // Since argv has only one element, n should be 0

    // Call the function-under-test
    uint32_t result = janet_optuinteger(argv, n, def, max);

    // Use the result in some way to prevent any compiler optimizations
    volatile uint32_t use_result = result;
    (void)use_result;

    return 0;
}