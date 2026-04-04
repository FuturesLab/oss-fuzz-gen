#include <stddef.h>
#include <stdint.h>
#include <linux/bpf.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    struct bpf_program *prog = NULL;
    struct bpf_object *obj = NULL;
    int err;

    // Create a BPF object from the input data
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Load the BPF object to get access to its programs
    err = bpf_object__load(obj);
    if (err) {
        bpf_object__close(obj);
        return 0;
    }

    // Iterate over programs in the BPF object
    bpf_object__for_each_program(prog, obj) {
        // Call the function-under-test
        __u32 line_info_count = bpf_program__line_info_cnt(prog);

        // Use the line_info_count in some way to avoid compiler optimizations
        if (line_info_count > 0) {
            // Do something trivial
            (void)line_info_count;
        }
    }

    // Clean up
    bpf_object__close(obj);

    return 0;
}