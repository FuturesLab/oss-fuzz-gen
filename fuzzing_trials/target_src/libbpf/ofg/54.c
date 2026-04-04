#include <stdint.h>
#include <stddef.h>
#include <linux/bpf.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    struct bpf_object *obj = bpf_object__open("dummy_bpf_program.o");
    if (!obj) {
        return 0;
    }

    // Ensure that the size of data is at least 4 bytes to read a __u32 value
    if (size < sizeof(__u32)) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first 4 bytes of data as the __u32 kversion
    __u32 kversion = *((__u32 *)data);

    // Call the function-under-test
    int result = bpf_object__set_kversion(obj, kversion);

    // Clean up
    bpf_object__close(obj);

    return 0;
}