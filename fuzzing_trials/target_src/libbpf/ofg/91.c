#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a bpf_prog_type value
    if (size < sizeof(enum bpf_prog_type)) {
        return 0;
    }

    // Extract the bpf_prog_type from the input data
    enum bpf_prog_type prog_type;
    memcpy(&prog_type, data, sizeof(enum bpf_prog_type));

    // Call the function-under-test
    const char *result = libbpf_bpf_prog_type_str(prog_type);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Simply print the result for debugging purposes
        printf("BPF Program Type: %s\n", result);
    }

    return 0;
}