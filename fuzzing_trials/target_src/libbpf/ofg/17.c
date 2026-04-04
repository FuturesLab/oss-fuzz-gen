#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    struct bpf_object *bpf_obj = NULL;
    struct btf *btf_obj = NULL;

    if (size == 0) {
        return 0;
    }

    // Initialize a bpf_object from the input data
    bpf_obj = bpf_object__open_mem(data, size, NULL);
    if (!bpf_obj) {
        return 0;
    }

    // Call the function-under-test
    btf_obj = bpf_object__btf(bpf_obj);

    // Clean up
    bpf_object__close(bpf_obj);

    return 0;
}