#include <stdint.h>
#include <stddef.h>  // Include this header to define size_t
#include <stdlib.h>  // Include this header for abort function

extern void janet_arity(int32_t, int32_t, int32_t);

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    if (size < 12) {
        return 0; // Ensure there is enough data for three int32_t values
    }

    int32_t arg1 = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
    int32_t arg2 = (int32_t)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]);
    int32_t arg3 = (int32_t)((data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11]);

    // Ensure that the arguments are within a valid range for the janet_arity function
    // Assuming janet_arity expects non-negative values
    if (arg1 < 0 || arg2 < 0 || arg3 < 0) {
        return 0;
    }

    // Additional check to ensure that the arguments are within a reasonable range
    // This is an assumption based on typical usage, adjust as necessary
    if (arg1 > 1000 || arg2 > 1000 || arg3 > 1000) {
        return 0;
    }

    janet_arity(arg1, arg2, arg3);

    return 0;
}