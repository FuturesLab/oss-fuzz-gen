#include <stdint.h>
#include <stdlib.h>
#include <linux/bpf.h>
#include "/src/libbpf/src/libbpf.h"

// Fuzzing harness for bpf_program__line_info
int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    struct bpf_program *prog = NULL;
    struct bpf_line_info *line_info;

    // Initialize a BPF object
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Load the BPF object
    if (bpf_object__load(obj) < 0) {
        bpf_object__close(obj);
        return 0;
    }

    // Get the first BPF program from the object
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Call the function-under-test
    line_info = bpf_program__line_info(prog);

    // Clean up
    bpf_object__close(obj);

    return 0;
}