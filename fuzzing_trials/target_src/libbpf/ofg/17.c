#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Ensure the data is null-terminated to safely use it as a string
    char *target = (char *)malloc(size + 1);
    if (!target) {
        return 0;
    }
    memcpy(target, data, size);
    target[size] = '\0';

    // Initialize libbpf
    libbpf_set_strict_mode(LIBBPF_STRICT_ALL);

    // Create a new BPF program object
    struct bpf_object *obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        free(target);
        return 0;
    }

    struct bpf_program *prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        free(target);
        return 0;
    }

    int attach_type = (int)data[0]; // Use the first byte of data as an integer

    // Call the function-under-test
    int result = bpf_program__set_attach_target(prog, attach_type, target);

    // Clean up
    bpf_object__close(obj);
    free(target);

    return 0;
}