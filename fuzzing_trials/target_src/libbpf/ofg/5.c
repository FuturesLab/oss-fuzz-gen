#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>  // Include this for memset
#include "/src/libbpf/src/libbpf.h"  // Corrected path for libbpf.h

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    struct bpf_program *prog_ptr;

    // Load BPF object and retrieve a program for fuzzing
    struct bpf_object *obj = bpf_object__open_file("test_bpf.o", NULL);
    if (!obj) {
        return 0;
    }

    // Load the BPF object
    if (bpf_object__load(obj)) {
        bpf_object__close(obj);
        return 0;
    }

    // Retrieve the first program in the BPF object
    prog_ptr = bpf_object__next_program(obj, NULL);
    if (!prog_ptr) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the boolean value
    bool autoattach = false;
    if (size > 0) {
        autoattach = (data[0] % 2 == 0);  // Use even/odd to determine true/false
    }

    // Call the function-under-test
    bpf_program__set_autoattach(prog_ptr, autoattach);

    // Clean up
    bpf_object__close(obj);

    return 0;
}