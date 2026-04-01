#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract necessary parameters
    if (size < sizeof(enum bpf_prog_type) + sizeof(enum bpf_func_id)) {
        return 0;
    }

    // Extract parameters from data
    enum bpf_prog_type prog_type = (enum bpf_prog_type)data[0];
    enum bpf_func_id func_id = (enum bpf_func_id)data[1];

    // The rest of the data is used as the const void* parameter
    const void *void_param = (const void *)(data + 2);

    // Call the function-under-test
    int result = libbpf_probe_bpf_helper(prog_type, func_id, void_param);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}