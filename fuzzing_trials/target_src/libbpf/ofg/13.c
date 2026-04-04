#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    struct bpf_program *prog;
    int attach_type;
    char *target;
    struct bpf_object *obj;

    // Ensure data size is sufficient for creating a string
    if (size < 1) {
        return 0;
    }

    // Load a dummy BPF object to initialize a bpf_program
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Get the first program from the BPF object
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Use the first byte of data to determine the attach_type
    attach_type = (int)data[0];

    // Allocate memory for the target string and copy data into it
    target = (char *)malloc(size);
    if (target == NULL) {
        bpf_object__close(obj);
        return 0;
    }
    memcpy(target, data + 1, size - 1);
    target[size - 1] = '\0'; // Ensure null-termination

    // Call the function-under-test
    bpf_program__set_attach_target(prog, attach_type, target);

    // Clean up
    free(target);
    bpf_object__close(obj);

    return 0;
}