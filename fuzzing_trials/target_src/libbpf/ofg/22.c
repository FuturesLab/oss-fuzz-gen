#include <stdint.h>
#include <linux/types.h>

extern __u32 libbpf_major_version();

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Call the function-under-test
    __u32 version = libbpf_major_version();

    // Use the version variable to prevent compiler optimizations from removing the call
    (void)version;

    return 0;
}