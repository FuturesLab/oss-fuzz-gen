#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Call the function-under-test
    uint32_t num_supported_boxes = gf_isom_get_num_supported_boxes();

    // Use the result in some way to avoid compiler optimizations removing the call
    if (num_supported_boxes > 0) {
        // Do something trivial with the result
        volatile uint32_t dummy = num_supported_boxes;
        (void)dummy;
    }

    return 0;
}