#include <stdint.h>
#include <stddef.h>
#include "/src/libbpf/src/libbpf.h"  // Corrected path for libbpf

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to interpret as an enum
    if (size < sizeof(enum bpf_attach_type)) {
        return 0;
    }

    // Cast the input data to a bpf_attach_type enum
    enum bpf_attach_type attach_type = *(const enum bpf_attach_type *)data;

    // Call the function-under-test
    const char *result = libbpf_bpf_attach_type_str(attach_type);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result) {
        // For example, print the result (in a real fuzzing environment, you might not print)
        // printf("Attach type string: %s\n", result);
    }

    return 0;
}