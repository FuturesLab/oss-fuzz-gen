#include <stdint.h>
#include <stddef.h>  // Include this header to define size_t
#include <stdlib.h>  // Include this header for abort()

extern void janet_arity(int32_t, int32_t, int32_t);

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    if (size < 12) {
        return 0; // Ensure we have enough data for three int32_t values
    }

    // Extract three int32_t values from the input data
    int32_t arg1 = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
    int32_t arg2 = (int32_t)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]);
    int32_t arg3 = (int32_t)((data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11]);

    // Ensure the arguments are within a reasonable range to prevent immediate crashes
    // Adjust the range based on the expected valid input range for janet_arity
    if (arg1 < 0 || arg2 < 0 || arg3 < 0 || arg1 > 1000 || arg2 > 1000 || arg3 > 1000) {
        return 0;
    }

    // Call the function-under-test with the extracted arguments
    janet_arity(arg1, arg2, arg3);

    return 0;
}