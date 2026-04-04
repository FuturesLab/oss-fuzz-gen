#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Define and initialize the parameters for the function-under-test
    enum bpf_prog_type prog_type;
    enum bpf_func_id func_id;
    const void *probe_data;

    // Ensure the input size is sufficient to extract the necessary parameters
    if (size < sizeof(prog_type) + sizeof(func_id)) {
        return 0;
    }

    // Extract the parameters from the input data
    prog_type = (enum bpf_prog_type)data[0];
    func_id = (enum bpf_func_id)data[1];
    probe_data = (const void *)(data + 2);

    // Call the function-under-test
    int result = libbpf_probe_bpf_helper(prog_type, func_id, probe_data);

    // Return the result
    return result;
}