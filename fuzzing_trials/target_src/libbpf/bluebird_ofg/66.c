#include <stddef.h>
#include <stdint.h>
#include <string.h>  // Include for memcpy
#include "libbpf.h"  // Correct include for libbpf

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    struct bpf_object *obj;
    struct bpf_map *map;
    int err;

    // Load BPF object from memory (assuming data is a valid BPF object file)
    obj = bpf_object__open_mem(data, size, NULL);
    if (!obj) {
        return 0;
    }

    // Load the BPF program
    err = bpf_object__load(obj);
    if (err) {
        bpf_object__close(obj);
        return 0;
    }

    // Get the first map in the BPF object
    map = bpf_object__next_map(obj, NULL);
    if (!map) {
        bpf_object__close(obj);
        return 0;
    }

    // Call the function-under-test
    int fd = bpf_map__fd(map);

    // Use the file descriptor to avoid unused variable warning
    // (In a real fuzzing scenario, further operations might be performed)
    (void)fd;

    // Clean up
    bpf_object__close(obj);

    return 0;
}