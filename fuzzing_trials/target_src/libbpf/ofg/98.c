#include <stdint.h>
#include <linux/types.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Call the function-under-test
    __u32 version = libbpf_minor_version();

    // Use the version variable in some way to avoid compiler optimizations
    // that might remove the call to libbpf_minor_version
    if (version == 0) {
        return 0;
    }

    return 0;
}