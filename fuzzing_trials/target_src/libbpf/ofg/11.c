#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient for our needs
    if (size < sizeof(enum bpf_prog_type) + sizeof(enum bpf_func_id)) {
        return 0;
    }

    // Extract enum bpf_prog_type from data
    enum bpf_prog_type prog_type = *(enum bpf_prog_type *)data;
    data += sizeof(enum bpf_prog_type);
    size -= sizeof(enum bpf_prog_type);

    // Extract enum bpf_func_id from data
    enum bpf_func_id func_id = *(enum bpf_func_id *)data;
    data += sizeof(enum bpf_func_id);
    size -= sizeof(enum bpf_func_id);

    // Use the remaining data as the const void * argument
    const void *arg = (const void *)data;

    // Call the function-under-test
    libbpf_probe_bpf_helper(prog_type, func_id, arg);

    return 0;
}