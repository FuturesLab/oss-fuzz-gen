#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"  // Correct path to libbpf.h

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for the function-under-test
    if (size < sizeof(enum bpf_map_type)) {
        return 0;
    }

    // Extract the enum bpf_map_type from the input data
    enum bpf_map_type map_type = *(enum bpf_map_type *)data;

    // Create a dummy pointer to pass as the second argument
    const void *dummy_ptr = (const void *)(data + sizeof(enum bpf_map_type));

    // Call the function-under-test
    int result = libbpf_probe_bpf_map_type(map_type, dummy_ptr);

    // Return 0 as required by the fuzzer
    return 0;
}