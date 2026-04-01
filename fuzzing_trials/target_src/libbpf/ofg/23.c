#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a meaningful test
    if (size < 2) {
        return 0;
    }

    // Initialize a bpf_program structure
    struct bpf_program *prog = NULL;  // Use a pointer to avoid incomplete type issue
    // Initialize a bpf_kprobe_multi_opts structure
    struct bpf_kprobe_multi_opts opts = {};

    // Use the first byte of data as a flag to set some option in opts
    opts.retprobe = data[0] & 1; // Use the first byte as a boolean flag for retprobe

    // Use the rest of the data as a string for the function name
    const char *func_name = (const char *)(data + 1);

    // Call the function-under-test
    struct bpf_link *link = bpf_program__attach_kprobe_multi_opts(prog, func_name, &opts);

    // Clean up if necessary (e.g., detach the link)
    if (link) {
        bpf_link__destroy(link);
    }

    return 0;
}