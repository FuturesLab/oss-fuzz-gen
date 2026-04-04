#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"
#include "/src/libbpf/src/bpf.h"
#include "/src/libbpf/src/libbpf_legacy.h" // Include the header where struct bpf_program is defined

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    struct bpf_program *prog;
    struct bpf_object *obj;

    // Create a new bpf_object to be used with bpf_program
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Get the first program from the object
    prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        bpf_object__close(obj);
        return 0;
    }

    // Call the function-under-test
    int fd = bpf_program__fd(prog);

    // Clean up
    bpf_object__close(obj);

    return 0;
}