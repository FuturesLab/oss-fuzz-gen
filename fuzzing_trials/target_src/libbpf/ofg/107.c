#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    struct bpf_program *prog = NULL;
    struct bpf_object *obj = NULL;
    struct bpf_object_open_opts opts = {};
    int err;

    // Create a bpf object from the input data
    obj = bpf_object__open_mem(data, size, &opts);
    if (!obj) {
        return 0;
    }

    // Load the bpf object to get the program
    err = bpf_object__load(obj);
    if (err) {
        bpf_object__close(obj);
        return 0;
    }

    // Get the first program in the object
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Call the function-under-test
    __u32 line_info_count = bpf_program__line_info_cnt(prog);

    // Clean up
    bpf_object__close(obj);

    return 0;
}