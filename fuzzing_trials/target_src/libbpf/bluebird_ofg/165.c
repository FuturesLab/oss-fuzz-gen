#include <stdint.h>
#include <stddef.h>
#include "libbpf.h"

int LLVMFuzzerTestOneInput_165(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract non-null strings
    if (size < 3) {
        return 0;
    }

    // Initialize the parameters for the function-under-test
    struct bpf_program *prog = (struct bpf_program *)data; // Casting data to a bpf_program pointer
    const char *category = (const char *)(data + 1); // Use data+1 as a string for category
    const char *name = (const char *)(data + 2); // Use data+2 as a string for name
    struct bpf_tracepoint_opts opts; // Initialize opts structure

    // Call the function-under-test
    struct bpf_link *link = bpf_program__attach_tracepoint_opts(prog, category, name, &opts);

    // Clean up if necessary
    if (link != NULL) {
        bpf_link__destroy(link);
    }

    return 0;
}