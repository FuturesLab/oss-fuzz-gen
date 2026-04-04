#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    struct bpf_program *prog = NULL;
    struct bpf_object *obj = NULL;
    struct bpf_program *iter;

    // Create a BPF object from the input data
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Load the BPF object
    if (bpf_object__load(obj) != 0) {
        bpf_object__close(obj);
        return 0;
    }

    // Iterate over all programs in the BPF object
    bpf_object__for_each_program(iter, obj) {
        // Attempt to autoload the BPF program
        bpf_program__autoload(iter);
    }

    // Clean up
    bpf_object__close(obj);

    return 0;
}