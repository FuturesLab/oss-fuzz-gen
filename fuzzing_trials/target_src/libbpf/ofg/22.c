#include "/src/libbpf/src/libbpf.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    struct bpf_program *program = NULL;
    int sockmap_fd = -1; // Initialize to an invalid file descriptor

    // Ensure we have enough data to construct a valid file descriptor
    if (size < sizeof(int)) {
        return 0;
    }

    // Use part of the data to create a pseudo file descriptor
    sockmap_fd = *((int *)data);
    data += sizeof(int);
    size -= sizeof(int);

    // Attempt to attach the BPF program to the sockmap
    struct bpf_link *link = bpf_program__attach_sockmap(program, sockmap_fd);

    // Cleanup: Detach and free the link if it was successfully created
    if (link != NULL) {
        bpf_link__destroy(link);
    }

    return 0;
}