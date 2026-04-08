#include <stdint.h>
#include <time.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    if (size < sizeof(time_t)) {
        return 0;
    }

    // Extract a time_t value from the input data
    time_t input_time;
    memcpy(&input_time, data, sizeof(time_t));

    // Call the function-under-test
    int offset = ly_time_tz_offset_at(input_time);

    // Use the result to prevent compiler optimizations
    (void)offset;

    return 0;
}