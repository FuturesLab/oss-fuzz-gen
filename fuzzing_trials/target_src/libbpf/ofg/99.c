#include <stdint.h>
#include <linux/types.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Call the function-under-test
    __u32 version = libbpf_minor_version();

    // Use the version value in some way to avoid compiler optimizations removing the call
    if (version == 0) {
        // This is just a placeholder to use the version value
        // Normally, you would have more logic here if needed
    }

    return 0;
}