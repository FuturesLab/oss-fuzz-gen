#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;
    int result;

    // Create a BPF object from the input data
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0; // If the object creation fails, return early
    }

    // Call the function-under-test
    result = bpf_object__load(obj);

    // Clean up
    bpf_object__close(obj);

    return 0;
}