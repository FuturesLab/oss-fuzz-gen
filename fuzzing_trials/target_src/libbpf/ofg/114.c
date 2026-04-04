#include <stdint.h>
#include <stddef.h>
#include <linux/bpf.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a bpf_map_type
    if (size < sizeof(enum bpf_map_type)) {
        return 0;
    }

    // Extract the bpf_map_type from the data
    enum bpf_map_type map_type = (enum bpf_map_type)(data[0] % BPF_MAP_TYPE_ARRAY); // Assuming BPF_MAP_TYPE_ARRAY as the max enum value

    // Use the remaining data as the void* input
    const void *void_input = (const void *)(data + sizeof(enum bpf_map_type));

    // Call the function under test
    int result = libbpf_probe_bpf_map_type(map_type, void_input);

    // Return the result or 0, depending on how you want to handle the output
    return result;
}