#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Assume a minimum size of 64 bytes for meaningful input
    if (size < 64) {
        return 0;
    }

    // Initialize a bpf_object from the data
    struct bpf_object *bpf_obj = bpf_object__open_mem(data, size, NULL);
    if (!bpf_obj) {
        return 0; // If object creation fails, exit
    }

    // Initialize bpf_map pointer
    struct bpf_map *bpf_map = NULL;

    // Call the function-under-test
    struct bpf_map *next_map = bpf_object__next_map(bpf_obj, bpf_map);

    // Clean up
    bpf_object__close(bpf_obj);

    // The function returns the next map or NULL if there are no more maps
    // No further action is needed for fuzzing, as we are testing for memory corruption

    return 0;
}