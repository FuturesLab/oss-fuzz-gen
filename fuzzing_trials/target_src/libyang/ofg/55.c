#include <stdint.h>
#include <stddef.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int offset = ly_time_tz_offset();

    // Use the result from the function call in some way to avoid compiler optimizations
    // that might remove the call if the result is not used.
    (void)offset;

    return 0;
}