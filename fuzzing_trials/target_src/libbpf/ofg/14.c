#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"  // Include the correct libbpf header

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    struct bpf_object *bpf_obj;
    struct bpf_program *bpf_prog;

    // Initialize bpf_object and bpf_program with non-NULL values
    bpf_obj = bpf_object__open_mem(data, size, NULL);
    if (!bpf_obj) {
        return 0; // Exit if object creation fails
    }

    // Load the BPF object to ensure that it contains programs
    if (bpf_object__load(bpf_obj) < 0) {
        bpf_object__close(bpf_obj);
        return 0;
    }

    // Get the first program from the object
    bpf_prog = bpf_object__next_program(bpf_obj, NULL);

    // Call the function-under-test
    struct bpf_program *prev_prog = bpf_object__prev_program(bpf_obj, bpf_prog);

    // Clean up
    bpf_object__close(bpf_obj);

    return 0;
}