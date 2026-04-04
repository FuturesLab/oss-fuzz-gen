#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to extract a valid bpf_map_type value
    if (size < sizeof(enum bpf_map_type)) {
        return 0;
    }

    // Extract a bpf_map_type value from the input data
    enum bpf_map_type map_type = (enum bpf_map_type)(data[0] % BPF_MAP_TYPE_ARRAY);

    // Call the function-under-test
    const char *result = libbpf_bpf_map_type_str(map_type);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result) {
        // Do something with the result, like printing or logging
    }

    return 0;
}