#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a bpf_prog_type value
    if (size < sizeof(enum bpf_prog_type)) {
        return 0;
    }

    // Extract a bpf_prog_type from the input data
    enum bpf_prog_type prog_type = *(const enum bpf_prog_type *)data;

    // Ensure the data pointer is not NULL and has at least one byte of data
    const void *probe_data = (const void *)(data + sizeof(enum bpf_prog_type));

    // Call the function-under-test
    int result = libbpf_probe_bpf_prog_type(prog_type, probe_data);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}