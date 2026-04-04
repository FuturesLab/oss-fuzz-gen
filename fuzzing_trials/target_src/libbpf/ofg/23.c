#include <stdint.h>
#include <linux/types.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Call the function-under-test
    __u32 version = libbpf_major_version();

    // Use the returned version number in some way to prevent compiler optimizations
    if (version == 0) {
        return 0;
    }

    return 0;
}